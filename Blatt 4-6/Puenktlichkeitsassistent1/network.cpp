#include "network.h"

#include <QMessageBox>
#include <QDebug>

#define MAX_BUFFER 256

WinNetworkInit::WinNetworkInit(WORD wVersionRequired /*= MAKEWORD(2, 2)*/) {
    m_wVersionRequired = wVersionRequired;
    m_nLastError = 0;
}

int WinNetworkInit::SysStartup() {
    int nStatus = NETWORK_NOERROR;

    m_nLastError = WSAStartup(m_wVersionRequired, &m_wsaData);

    if (m_nLastError)
        nStatus = NETWORK_WINSOCK_ERROR;

    return nStatus;
}

int WinNetworkInit::SysShutdown() {
    int nStatus = NETWORK_NOERROR;

    if(WSACleanup() != 0)
    {
        m_nLastError = WSAGetLastError();
        nStatus = NETWORK_WINSOCK_ERROR;
    }

    return nStatus;
}

void WinNetworkInit::SysInformation(LPWSADATA pwsaData) {
    memcpy(pwsaData, &m_wsaData, sizeof(WSADATA));
}

WinStreamNetwork::WinStreamNetwork() : m_nLastError(0),
    m_s(INVALID_SOCKET) {
    memset(&m_sinRemote, 0, sizeof(SOCKADDR_IN));
    memset(&res, 0, sizeof(addrinfo));
}

int WinStreamNetwork::SysCreateSocket(int nLocalPort) {
    if (nLocalPort <= 0)
        return NETWORK_FALSE_ARGUMENT_ERROR;

    int nStatus = NETWORK_NOERROR;
    /* make sure the socket isn't already created */
    if (m_s != INVALID_SOCKET)
        return NETWORK_PROGRAMMING_ERROR;



    return nStatus;
}

int WinStreamNetwork::Connect(LPSTR pszRemoteName, int nRemotePort) {
    SOCKADDR_IN sinRemote;
    addrinfo *pResult = nullptr;
    addrinfo hints, *p;
    int nStatus = NETWORK_NOERROR;

    sinRemote.sin_family = AF_INET;
    sinRemote.sin_port = htons(nRemotePort);

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    char pszRemoteService[18];
    _itoa(nRemotePort, pszRemoteService, 10);

    if (getaddrinfo(pszRemoteName, pszRemoteService, &hints, &pResult) != 0)
        return NETWORK_FALSE_ARGUMENT_ERROR;

    for (p=pResult; p!=NULL; p = p->ai_next)
    {
        // create the socket
        if(m_s = socket(p->ai_family, p->ai_socktype, p->ai_protocol) ==
                SOCKET_ERROR) {
            continue;
        }

        SOCKADDR_IN *sockaddr_ipv4 = reinterpret_cast<sockaddr_in*>
                (pResult->ai_addr);
        qDebug() << inet_ntoa(sockaddr_ipv4->sin_addr);

        if (connect(m_s, p->ai_addr, p->ai_addrlen) ==
                SOCKET_ERROR) {
            closesocket(m_s);
            m_s = NULL;
            continue;
        }

        break;
    }

    if (m_s == INVALID_SOCKET)
    {
        m_nLastError = WSAGetLastError();
        nStatus = NETWORK_WINSOCK_ERROR;
    }
}

int WinStreamNetwork::Write(void *data, int len) {
    return 0;
}

void WinStreamNetwork::Close() {
    if (m_s) {
        closesocket(m_s);
    }
}

bool Network::Connect(const QString &hostName, const int port) {
    if (m_sysNetworkInit.SysStartup() != NETWORK_NOERROR)
        return false;

    if (m_sysStreamNetwork.SysCreateSocket(port) != NETWORK_NOERROR)
        return false;

    QByteArray ba = hostName.toLatin1();

    if(m_sysStreamNetwork.Connect(ba.data(), port) != NETWORK_NOERROR)
        return false;

   if (m_openSSL.Connect(m_sysStreamNetwork.getSocket()) != NETWORK_NOERROR)
       return false;

    return true;
}

int Network::Write(const QString &message, bool useSSL) {
    int ret = 0;
    QByteArray ba = message.toLatin1();
    if (useSSL) {
        ret = m_openSSL.Write(ba.data(), ba.size());
    } else {
        ret = m_sysStreamNetwork.Write(ba.data(), ba.size());
    }
    return ret;
}

void Network::Close() {
    m_openSSL.Close();
    m_sysStreamNetwork.Close();
    m_sysNetworkInit.SysShutdown();
}

int OpenSSL::Startup() {
    SSL_load_error_strings();

    // start with TLS/SSL intitalization
    // must be called before any other calls to SSL
    SSL_library_init();

    // creates a new SSL_CTX object to establish TLS/SSL
    // enabled connections
    m_ssl_ctx = SSL_CTX_new (SSLv23_client_method());

    return NETWORK_NOERROR;
}

int OpenSSL::Write(void *buf, int len) {

    // writes our message into the ssl connection.
    int n = SSL_write(m_conn, buf, len);

    if (n <= 0) {
        int ioError = SSL_get_error(m_conn, n);
        /*MessageBox(NULL, L"OpenSSL Error:", L"SSL couldn't write.",
                   MB_OK | MB_ICONERROR);*/
        return NETWORK_OPENSSL_ERROR;
    }

    return NETWORK_NOERROR;
}

int OpenSSL::Read() {
    char buffer[MAX_BUFFER];
    int n = 0;

    memset(buffer, 0, MAX_BUFFER);

    do {
        // read bytes from a TLS/SSL connection
        n = SSL_read(m_conn, buffer, MAX_BUFFER);
    } while((n = SSL_pending(m_conn)) <= 0);
    qDebug() << buffer;

    return n;
}

int OpenSSL::Connect(const SOCKET s) {
    int errorCode = 0;
    // creates a new SSL structure which is needed to hold
    // the data for a TLS/SSL connection.
    m_conn = SSL_new(m_ssl_ctx);

    // sets the socket descriptoras the input/output facility
    // for the (encrypted) side of SSL.
    if (SSL_set_fd(m_conn, s) == 0) {
        /*MessageBox(NULL, L"OpenSSL Error:", L"Couldn't set file descriptor to SSL.",
                   MB_OK | MB_ICONERROR);*/
        return NETWORK_OPENSSL_ERROR;
    }

    // initiate the TLS/SSL handshake with an TLS/SSL server
    errorCode = SSL_connect(m_conn);
    if (errorCode <= 0) {
        int ioError = SSL_get_error(m_conn, errorCode);
        /*MessageBox(NULL, L"OpenSSL Error:", L"SSL couldn't connect with Server.",
                   MB_OK | MB_ICONERROR);*/
        return NETWORK_OPENSSL_ERROR;
    }

    return NETWORK_NOERROR;
}

void OpenSSL::Close() {
    SSL_shutdown(m_conn);
    SSL_free(m_conn);
    SSL_CTX_free(m_ssl_ctx);
}


void MyNetwork::activateLamp() {
    if(Connect("localhost", 90)==NETWORK_NOERROR)
        return;
}

void MyNetwork::getDirection() {
    QString querie = "GET /maps/api/directions/json?origin=Lotstrasse,Munich,DE&destination=Kleinstrasse,Munich";
    QString host = "maps.googleapis.com";
    if(!Connect(host, 443))
        return;
    Write(querie, true);
    Close();
}

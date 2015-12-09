#include "network.h"

#include <openssl/err.h>
#include <QMessageBox>
#include <QDebug>

#define MAX_BUFFER 512

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
        // create the socket for connecting to server
        m_s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (m_s == INVALID_SOCKET)
        {
            m_nLastError = WSAGetLastError();
            nStatus = NETWORK_WINSOCK_ERROR;
        }

        SOCKADDR_IN *sockaddr_ipv4 = reinterpret_cast<sockaddr_in*>
                (pResult->ai_addr);
        qDebug() << inet_ntoa(sockaddr_ipv4->sin_addr);

        // connect to the server
        if (connect(m_s, p->ai_addr, p->ai_addrlen) ==
                SOCKET_ERROR) {
            m_nLastError = WSAGetLastError();
            closesocket(m_s);
            m_s = INVALID_SOCKET;
            continue;
        }

        break;
    }

    return NETWORK_NOERROR;
}

int WinStreamNetwork::Write(void *data, int len) {
    // Send an initial
    int n= 0;
    n = send( m_s, (char*)data, len, 0 );
    if (n == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(m_s);
        WSACleanup();
        return NETWORK_WINSOCK_ERROR;
    }
    return NETWORK_NOERROR;
}

QByteArray WinStreamNetwork::Read() {
    char buf[MAX_BUFFER];
    int n = 0;
    do {
        n = recv(m_s, buf, MAX_BUFFER, 0);
        if (n > 0)
            qDebug() << "Bytes empfangen: " << n << "\n";
    } while (n > 0 && n == MAX_BUFFER);

    return buf;
}

void WinStreamNetwork::Close() {
    if (m_s) {
        closesocket(m_s);
    }
}

bool Network::Connect(const QString &hostName, const int port, bool useSSL) {
    if (m_sysNetworkInit.SysStartup() != NETWORK_NOERROR)
        return false;

    QByteArray ba = hostName.toLatin1();

    if(m_sysStreamNetwork.Connect(ba.data(), port) != NETWORK_NOERROR)
        return false;

    m_useSSL = useSSL;
    if(m_useSSL) {
        m_openSSL.Startup();
        if (m_openSSL.Connect(m_sysStreamNetwork.getSocket()) != NETWORK_NOERROR)
            return false;
    }

    return true;
}

int Network::Write(const QString &message) {
    int ret = 0;
    QByteArray ba = message.toLatin1();
    if (m_useSSL) {
        ret = m_openSSL.Write(ba.data(), ba.size());
    } else {
        ret = m_sysStreamNetwork.Write(ba.data(), ba.size());
    }
    return ret;
}

 QString Network::Read() {
     if (m_useSSL)
         return m_openSSL.Read();
     else
         return m_sysStreamNetwork.Read();
 }

void Network::Close() {
    if (m_useSSL)
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
    qDebug() << (char*)buf << "\n";
    // writes our message into the ssl connection.
    int n = SSL_write(m_conn, (char*)buf, len);

    if (n <= 0) {
        int ioError = SSL_get_error(m_conn, n);
        /*MessageBox(NULL, L"OpenSSL Error:", L"SSL couldn't write.",
                   MB_OK | MB_ICONERROR);*/
        return NETWORK_OPENSSL_ERROR;
    }

    return NETWORK_NOERROR;
}

QByteArray OpenSSL::Read() {
    QByteArray received;
    received.reserve(4096); // pre allocate 4k space
    int n = 0;
    char buffer[MAX_BUFFER]; // packets will be send in MAX_BUFFER size
    memset(buffer, 0, MAX_BUFFER);

    do {
        // read bytes from a TLS/SSL connection
        n = SSL_read(m_conn, buffer, MAX_BUFFER);
        if (n > 0)
            qDebug() << "Bytes empfangen: " << n << "\n";

        received += buffer;
    } while(n > 0);

    return received;
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
        long error = ERR_get_error();
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


bool MyNetwork::activateLamp(long color) {
    QString body = "{\"on\":true,\"bri\":254,\"hue\":";
    body += QString::number(color);
    body += ",\"sat\":254}";
    QString post = "PUT /api/newdeveloper/lights/2/state";
    post += " HTTP/1.1\r\n";
    post += "Content-Length: ";
    post += QString::number(body.length());
    post += "\r\n\r\n";
    post += body + "\r\n\r\n";

    if(!Connect("127.0.0.1", 8000, false))
        return false;

    Write(post);
    QString reply = Read();

    qDebug() << reply;

    Close();

    return true;
}

QString MyNetwork::getDirection(const QString& message) {
    QString reply;
    QString request = message + "\nHTTP/1.1\r\n"
              "Host: maps.googleapis.com\r\n";
    QString host = "maps.googleapis.com";
    if(!Connect(host, 443, true))
        return reply;
    if(Write(request) != NETWORK_NOERROR) {
        return reply;
    }
    qDebug() << "Anfrage versendet warte auf Antwort...\n";
    reply = Read();
    Close();

    return reply;
}

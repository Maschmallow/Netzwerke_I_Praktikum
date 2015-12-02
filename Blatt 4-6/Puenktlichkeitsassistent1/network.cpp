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

int WinStreamNetwork::SysCreateSocket(int nLocalPort) {
    if (nLocalPort <= 0)
        return NETWORK_FALSE_ARGUMENT_ERROR;

    int nStatus = NETWORK_NOERROR;
    /* make sure the socket isn't already created */
    if (m_s != INVALID_SOCKET)
        return NETWORK_PROGRAMMING_ERROR;

    // create the socket
    m_s = socket(PF_INET, SOCK_STREAM, 0);

    if (m_s == INVALID_SOCKET)
    {
        m_nLastError = WSAGetLastError();
        nStatus = NETWORK_WINSOCK_ERROR;
    }

    return nStatus;
}

int WinStreamNetwork::Connect(LPSTR pszRemoteName, int nRemotePort) {
    SOCKADDR_IN sinRemote;
    addrinfo *pResult = nullptr;
    addrinfo hints;

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

    if (pResult == nullptr)
        return NETWORK_FALSE_ARGUMENT_ERROR;

    if(pResult->ai_family == AF_INET)
        memcpy(&sinRemote.sin_addr, &pResult->ai_addr, sizeof(SOCKADDR_IN));

    freeaddrinfo(pResult);

    return Connect(&sinRemote);
}

int WinStreamNetwork::Connect(LPSOCKADDR_IN psinRemote) {
    int errorCode = NETWORK_NOERROR;
    memcpy(&m_sinRemote, psinRemote, sizeof(SOCKADDR_IN));

    if (connect(m_s, (LPSOCKADDR)&m_sinRemote, sizeof(SOCKADDR_IN)) ==
            SOCKET_ERROR)
    {
        m_nLastError = WSAGetLastError();
        if (m_nLastError == WSAEWOULDBLOCK)
            m_nLastError = 0;
        else
            errorCode = NETWORK_WINSOCK_ERROR;
    }

    return NETWORK_NOERROR;
}

bool Network::Connect(const QString &hostName, const int port) {
    if (m_sysNetworkInit.SysStartup() != NETWORK_NOERROR)
        return false;
    QByteArray ba = hostName.toLatin1();
    m_sysStreamNetwork.Connect(ba.data(), port);

    return true;
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

int OpenSSL::Write(char *buf, int len) {
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

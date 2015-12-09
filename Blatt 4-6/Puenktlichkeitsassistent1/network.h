#ifndef NETWORK_H
#define NETWORK_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <openssl/ssl.h>

#include <QString>

enum NETWORKERRORCODE {
    NETWORK_NOERROR,
    NETWORK_WINSOCK_ERROR,
    NETWORK_FALSE_ARGUMENT_ERROR,
    NETWORK_PROGRAMMING_ERROR,
    NETWORK_OPENSSL_ERROR
};

class WinNetworkInit {
public:
    WinNetworkInit(WORD wVersionRequired = MAKEWORD(2, 2));
    int SysStartup();
    int SysShutdown();
    void SysInformation(LPWSADATA pwsaData);
    int SysLastError() const { return m_nLastError; }

private:
    WSADATA m_wsaData;
    int m_nLastError;
    WORD m_wVersionRequired;
};

// For tcp connections
class WinStreamNetwork {
private:
    int m_nLastError;
    SOCKET m_s;
    SOCKADDR_IN m_sinRemote;
    addrinfo res;
public:
    WinStreamNetwork();

    int SysDestroySocket();

    // Establish TCP connection
    int Connect(LPSTR pszRemoteName, int nRemotePort);

    void Close();

    int Write(void *data, int len);
    QByteArray Read();

    SOCKET getSocket() const { return m_s; }
};

class OpenSSL {
private:
    SSL *m_conn;
    SSL_CTX *m_ssl_ctx;
public:
    int Startup();
    int Connect(const SOCKET s);
    int Write(void *data, int len);
    QByteArray Read();
    void Close();
};

class Network {
private:
    WinNetworkInit m_sysNetworkInit;
    WinStreamNetwork m_sysStreamNetwork;
    OpenSSL m_openSSL;
    bool m_useSSL;
public:
    bool Connect(const QString &hostName, const int port, bool useSSL);
    int Write(const QString &message);
    void Close();
    QString Read();
};

class MyNetwork : public Network {
public:
    bool activateLamp(long color);
    QString getDirection(const QString& message);
};

#endif // NETWORK_H


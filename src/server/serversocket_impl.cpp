#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>
#include <cstring>

#include "iserversocket.hpp"


using namespace std;

namespace
{
    const int PORT = 1372;
}

class ServerSocketImpl: public iServerSocket {

    sockaddr_in m_servAddr;
    int m_serverSd;
    int m_clientSd;

public:

    ServerSocketImpl()
            : m_serverSd(socket(AF_INET, SOCK_STREAM, 0))
    {
        bzero((char*)&m_servAddr, sizeof(m_servAddr));
        m_servAddr.sin_family = AF_INET;
        m_servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        m_servAddr.sin_port = htons(PORT);
    }

    virtual int bind() override
    {
        int bindStatus = ::bind(m_serverSd, (struct sockaddr*) &m_servAddr,
                              sizeof(m_servAddr));
        return bindStatus;
    }

    virtual void listen() override
    {
        ::listen(m_serverSd, 5);
    }

    virtual int accept() override
    {
        sockaddr_in clientSockaddr_in;
        socklen_t clientSockAddrSize = sizeof(clientSockaddr_in);
        m_clientSd = ::accept(m_serverSd, (sockaddr *)&clientSockaddr_in, &clientSockAddrSize);
        return m_clientSd;
    }
        
    void close() override
    {
        ::close(m_clientSd);
        ::close(m_serverSd);
    }

    int sendMessage(const std::string& message) override
    {
        return send(m_clientSd, message.c_str(), sizeof(message), 0);
    }

    int receiveMessage(std::string& received_message) override
    {
        char buff[128];
        memset(buff, 0, sizeof(buff));

        int bytes = ::recv(m_clientSd, (char*)buff, sizeof(buff), 0);
        std::string s(buff);
        received_message = s;
        return bytes;
    }
};

std::unique_ptr<iServerSocket> createServerSocket()
{
    return std::make_unique<ServerSocketImpl>();
}

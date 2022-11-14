//
// Created by arman on 10/29/22.
//

#include "isocket.hpp"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory>
#include <cstring>

using namespace std;

namespace
{
    const char *IP_ADDRESS = "localhost";
    const int PORT = 1345;
}

class SocketImpl: public iSocket {

    sockaddr_in m_servAddr;
    int m_serverSd;
    int m_clientSd;

public:

    SocketImpl()
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
        std::cout<<"server bind  "<<bindStatus<<std::endl;
        return bindStatus;
    }

    virtual void listen() override
    {
        //listen for up to 5 requests at a time
        std::cout<<"server listen"<<std::endl;
        ::listen(m_serverSd, 5);
    }

    virtual int accept() override
    {
        sockaddr_in clientSockaddr_in;
        socklen_t clientSockAddrSize = sizeof(clientSockaddr_in);
        m_clientSd = ::accept(m_serverSd, (sockaddr *)&clientSockaddr_in, &clientSockAddrSize);
        std::cout<<"server accept socket = " << m_clientSd <<std::endl;
        return m_clientSd;
    }
        
    void close() override
    {
        ::close(m_clientSd);
        ::close(m_serverSd);
        std::cout << "Connection closed..." << std::endl;
    }


    int sendMessage(const std::string& message) override
    {
        return send(m_clientSd, message.c_str(), sizeof(message), 0);
    }

    int receiveMessage(std::string& received_message) override
    {
        char buff[128];
        memset(buff, 0, sizeof(buff));

        int read = ::recv(m_clientSd, (char*)buff, sizeof(buff), 0);
        std::string s(buff);
        received_message = s;
        return read;
    }
};

std::unique_ptr<iSocket> createSocket()
{
    return std::unique_ptr<SocketImpl>(new SocketImpl());
}

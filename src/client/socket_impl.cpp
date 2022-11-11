//
// Created by arman on 10/29/22.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/time.h>
#include <memory>

#include "isocket.hpp"
#include <stdexcept>

namespace
{
    const char *IP_ADDRESS = "localhost";
    const int PORT = 1333;
}

class SocketImpl: public iSocket {

    sockaddr_in m_sendSockAddr;
    int m_clientSd;

public:

    SocketImpl()
        : m_clientSd(socket(AF_INET, SOCK_STREAM, 0))
    {
        const auto& host = gethostbyname(IP_ADDRESS);
        std::cout<<"socket id" << m_clientSd<<std::endl;
        m_sendSockAddr.sin_addr.s_addr =
                inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
        m_sendSockAddr.sin_port = htons(PORT);
        m_sendSockAddr.sin_family = AF_INET;
    }


    int sendMessage(const std::string& message)
    {
        return ::send(m_clientSd, (char*)message.c_str(), message.length() + 1, 0);
    }

    bool receiveMessage() 
    {
        std::cout << "Awaiting server response..." << std::endl;
        //FIXME Need to be improved
        int message;
        int status = recv(m_clientSd, (char*)&message, sizeof(message), 0);
        std::cout << message << std::endl;
        return status;
    }

    void close() 
    {
        ::close(m_clientSd);
        std::cout << "Connection closed!" << std::endl;
    }

    int connect()
    {
        return ::connect(m_clientSd,
                (sockaddr*) &m_sendSockAddr, sizeof(m_sendSockAddr));
    }

};

std::unique_ptr<iSocket> createSocket() {
    return std::unique_ptr<iSocket>(new SocketImpl());
}

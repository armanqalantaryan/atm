//
// Created by arman on 10/29/22.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <memory>
#include <cstring>

#include "isocket.hpp"

namespace
{
    const char *IP_ADDRESS = "localhost";
    const int PORT = 1371;
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

    bool receiveMessage(std::string& received_message)
    {
        std::cout << "Awaiting server response..." << std::endl;
        char buff[124];
        memset(buff, 0, sizeof(buff));

        int status = recv(m_clientSd, (char*)buff, sizeof(buff), 0);
        std::string s(buff);
        received_message = s;
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

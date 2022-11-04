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
#include <bitset>

#include "isocket.hpp"
#include <stdexcept>

namespace
{
    const char *IP_ADDRESS = "localhost";
    const int PORT = 1245;
}

class SocketImpl: public iSocket {
private:
    sockaddr_in m_sendSockAddr;
    const int m_clientSd;

public:

    SocketImpl(): m_clientSd(socket(AF_INET, SOCK_STREAM, 0)) {
        const auto& host = gethostbyname(IP_ADDRESS);

        m_sendSockAddr.sin_addr.s_addr =
                inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
        m_sendSockAddr.sin_port = htons(PORT);
        m_sendSockAddr.sin_family = AF_INET;
    }


    bool sendMessage(std::string& message) {
        return send(m_clientSd, message.c_str(), sizeof(message), 0);
    }

    bool receiveMessage() {
        std::cout << "Awaiting server response..." << std::endl;
        //FIXME Need to be improved
        int message;
        int status = recv(m_clientSd, (char*)&message, sizeof(message), 0);
        std::cout << message << std::endl;
        return status;
    }
    const std::string makeString(const std::string& choice,const std::string& card_number,const std::string& pin) {
        std::bitset<4> b1(choice);
        std::bitset<16> b2(card_number);
        std::bitset<6> b3(pin);
        std::cout <<"Data to send choice" << b1<<"  card "<< b2<<"  pin "<< b3  std::endl;

        const res = b1 + b2 + b3;
        return res ;
    }


    void closeSocket() {
        close(m_clientSd);
        std::cout << "Connection closed!" << std::endl;
    }

    void connectSocket() {
        int status = connect(m_clientSd,
                             (sockaddr*) &m_sendSockAddr, sizeof(m_sendSockAddr));
        if(status < 0)
        {
            throw std::runtime_error("Error connecting to the Server!");
        }
        std::cout << "Connected to the Server!" << std::endl;
    }

};

std::unique_ptr<iSocket> createSocket() {
    return std::unique_ptr<iSocket>(new SocketImpl());
}

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
#include <stdexcept>
#include <strings.h>

using namespace std;

namespace
{
    const char *IP_ADDRESS = "localhost";
    const int PORT = 1253;
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
        //initialize();
    }

    virtual int bind() override
    {
        int bindStatus = ::bind(m_serverSd, (struct sockaddr*) &m_servAddr,
                              sizeof(m_servAddr));
        std::cout<<"server bind  "<<m_serverSd<<std::endl;
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
        
        /*if(m_clientSd < 0)
        {
            std::cout<<"Error accepting request from client!";
            return false;
        }*/
    }

    /*void initialize()
    {
        int rc;
        char* sql;
        rc = sqlite3_open("atm.db", &m_db);
        if(rc)
        {
            std::cerr << "Can`t open database "<< std::endl << sqlite3_errmsg(m_db);
        } else
        {
            std::cout << "Opened database successfully" << std::endl;
        }

        sql = "create table if not exists user("                    \
          " card_number BIGINT primary key not null,"           \
          " pin_code int not null,"                             \
          " balance int not null"                               \
          ");";

        *//*      "               insert into user (card_number,pin_code,balance)" \
          "             values (5510266988745563, 7860,561000);" \
          "               insert into user (card_number,pin_code,balance)" \
          "             values (7896632144785914, 9547,12000050);" \
          "               insert into user (card_number,pin_code,balance)" \
          "             values (7889965412233585, 8547,78500);" \
          "               insert into user (card_number,pin_code,balance)" \
          "             values (7889566221455895, 1114,754000);" \
          "               insert into user (card_number,pin_code,balance)" \
          "             values (7894555648897552, 5889,899600);";*//*

        sqlite3_exec(m_db,sql, nullptr,0,0);
    }
*/
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

    int receiveMessage(char* buff) override
    {
        cout << " 11111111111111 " << endl;
        char b[1024];
        int count;

        while ((count = ::recv(m_clientSd, (char*)&b, sizeof(b), 0) > 0))
        {
            cout << " 22222222222222 " << count << endl;
            //break;
        }
        cout << " 333333333333333333 "  << count << endl;
        //int res = recv(m_clientSd, *buff, 84, MSG_WAITALL);
        //int res = recv(m_clientSd, *buff, 84, MSG_DONTWAIT);
        return count;
    }
};

std::unique_ptr<iSocket> createSocket()
{
    return std::unique_ptr<SocketImpl>(new SocketImpl());
}

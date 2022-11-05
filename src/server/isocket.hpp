//
// Created by arman on 10/29/22.
//
#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>

class iSocket {
public:
    virtual void closeSocket() = 0;
    virtual int sendMessage(const stdLLstring&) = 0;
    virtual bool receiveMessage() = 0;
    virtual bool startServer() = 0;



};

#endif //SERVER_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <memory>
#include <cstring>

#include "iclientsocket.hpp"

namespace
{
    const std::string IP_ADDRESS = "localhost";
    const int PORT = 1372;
}

class ClientSocketImpl: public iClientSocket {

    sockaddr_in m_sendSockAddr;
    int m_clientSd;

public:

    ClientSocketImpl()
        : m_clientSd(socket(AF_INET, SOCK_STREAM, 0))
    {
        const auto& host = gethostbyname(IP_ADDRESS.c_str());
        m_sendSockAddr.sin_addr.s_addr =
                inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
        m_sendSockAddr.sin_port = htons(PORT);
        m_sendSockAddr.sin_family = AF_INET;
    }


    int sendMessage(const std::string& message) override
    {
        return ::send(m_clientSd, (char*)message.c_str(), message.length() + 1, 0);
    }

    bool receiveMessage(std::string& received_message) override
    {
        char buff[124];
        memset(buff, 0, sizeof(buff));

        int status = recv(m_clientSd, (char*)buff, sizeof(buff), 0);
        std::string s(buff);
        received_message = s;
        return status;
    }

    void close() override
    {
        ::close(m_clientSd);
    }

    int connect() override
    {
        return ::connect(m_clientSd,
                (sockaddr*) &m_sendSockAddr, sizeof(m_sendSockAddr));
    }

};

std::unique_ptr<iClientSocket> createClientSocket()
{
    return std::make_unique<ClientSocketImpl>();
}

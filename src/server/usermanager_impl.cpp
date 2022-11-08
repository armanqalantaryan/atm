#include "iusermanager.hpp"
#include <iostream>
#include "sqlite3.h"

using namespace std;

class UserManager : public iUserManager
{
    std::unique_ptr<iSocket> m_socket;
   // sqlite3* m_db;


public:

    bool cardRegistration() override
    {
        return true;
    }

    bool cardCheck() override
    {
        return true;
    }

    bool receiveMessage(std::string& s) override
    {
        char buff[1024];
        int response = m_socket->receiveMessage((char*)&buff);

        bool res = false;
        
        if (response > 0)
        {
           cout << "*** Response size *** " << response << endl;
           s = std::string(buff); 
           cout << "*** Response message *** " << s << endl;
           res = true;
        }

        return res;
    }

    bool connect_socket(std::unique_ptr<iSocket> socket) override
    {
        m_socket = std::move(socket);
        if(m_socket->bind() < 0)
        {
            return false;
        }
        std::cout<< "bind complete"<<std::endl;
        m_socket->listen();
        if(m_socket->accept() < 0)
        {
            return false;
        }
        std::cout <<"socket connect"<<std::endl;
        return true;
    }
};

std::unique_ptr<iUserManager> createUserManager()
{
    return std::unique_ptr<iUserManager>(new UserManager());
}

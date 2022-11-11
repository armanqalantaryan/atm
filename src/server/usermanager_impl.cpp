#include <iostream>

#include "iusermanager.hpp"

using namespace std;

class UserManagerImpl : public iUserManager
{
    std::unique_ptr<iSocket> m_socket;
    std::unique_ptr<iDb> m_db;
    std::string m_card_number;
    std::string m_pin;

public:

    void processMessage() override
    {
        string received_message;
        int read = m_socket->receiveMessage(received_message);

        cout << "*** Reveived message *** " << received_message << endl;

        if(received_message.length() != 17) {
            std::cout << "Invalid message" << std::endl;
            return;
        }
        m_card_number = received_message.substr(1,12);
        m_pin = received_message.substr(13,4);
        if (read > 0)
        {
            // TODO
           auto process_type = received_message[0];

           if (process_type == '1')
           {
               cardRegistration();
               // TODO registration
           }
           else if (process_type == '2')
           {
               //TODO process card
           }

        }

    }

    bool connect_db(std::unique_ptr<iDb> db) override
    {
       m_db = std::move(db);
       return m_db->init();
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

private:

    bool cardRegistration()
    {
        cout << "*** In process regstration  *** " << endl;
        int sent;
        if(m_db->write(m_card_number,m_pin))
        {
           sent = m_socket->sendMessage("1");
        }
        return (sent > 0) ? true : false;
    }

    bool cardCheck()
    {
        return true;
    }

};

std::unique_ptr<iUserManager> createUserManager()
{
    return std::unique_ptr<iUserManager>(new UserManagerImpl());
}

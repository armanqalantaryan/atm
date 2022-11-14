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
        if(read > 0)
        {
            m_card_number = received_message.substr(1,12);
            std::cout<<" card_number ----  " << m_card_number<<std::endl;
            m_pin = received_message.substr(13);
            std::cout<<" pin ----  " << m_pin<<std::endl;

            // TODO
           auto process_type = received_message[0];

           if (process_type == '1')
           {
               std::cout << "in process message" << std::endl;
               cardRegistration();
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
            std::cout<<"bind error"<<std::endl;
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
        if(m_db->write(m_card_number, m_pin))
        {
            cout << "*** DB Written *** " << endl;
           //sent = m_socket->sendMessage("1");
           sent = 1;
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

#include <iostream>
#include <cassert>

#include "iusermanager.hpp"
#include "utilities.hpp"

using namespace std;


namespace {

    const string DB_NAME = "atm.db";
    const string TABLE_NAME = "user";
    const string COL_CARD_NUMBER = "card_number";
    const string COL_PIN = "pin";
    const string COL_BALANCE = "balance";
}

class UserManagerImpl : public iUserManager
{
    std::unique_ptr<iSocket> m_socket;
    std::unique_ptr<iSqlDB> m_db;
    std::string m_card_number;
    std::string m_pin;
    string m_received_message;

public:

    bool connect_db(std::unique_ptr<iSqlDB> db) override
    {
       m_db = std::move(db);
       m_db->connect(DB_NAME);
       auto res = m_db->runSql(makeSql("create table if not exists", TABLE_NAME, "(", COL_CARD_NUMBER, "TEXT,", COL_PIN, "TEXT,", COL_BALANCE, "TEXT);"));
       return (res.second == 0) ? true : false;
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

    void processMessage() override
    {
        int received = m_socket->receiveMessage(m_received_message);
        if(received > 0)
        {
            m_card_number = m_received_message.substr(1,12);
            m_pin = m_received_message.substr(13, 4);

            auto process_type = m_received_message[0];

            if (process_type == '1')
            {
                cardRegistration();
            }
            else if (process_type == '2')
            {
                //TODO process card
            }
        }
    }

private:

    void cardRegistration()
    {
        auto res = m_db->runSql(makeSql("select", COL_CARD_NUMBER,"from", TABLE_NAME,
                    "where", COL_CARD_NUMBER , "=", m_card_number));

        if(res.first.empty())
        {
            auto user_reg = m_db->runSql(makeSql("insert", "into", TABLE_NAME, "(", COL_CARD_NUMBER, ",", COL_PIN,  ",",  COL_BALANCE, ")",
                        "values", "(", m_card_number, ",", m_pin, ",", "0",")"));
            if(user_reg.second > 0)
            {
                std::cout << "DB error" << std::endl;
                throw;
            }
            cout << "*** DB Written *** " << endl;
        } 
        else
        {
            std::cout << "Card number already exists" << std::endl;
            // send to client
        }
    }

};

std::unique_ptr<iUserManager> createUserManager()
{
    return std::unique_ptr<iUserManager>(new UserManagerImpl());
}

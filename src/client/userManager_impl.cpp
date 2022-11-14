
#include "iusermanager.hpp"
#include "isocket.hpp"

#include <iostream>
#include <bitset>

using namespace std;

namespace {

    const string proc_reg = "1";
    const string proc_card = "2";


    // helper function
    std::string makeString(const std::string& choice,const std::string& message2,const std::string& message3) 
    {
        std::bitset<4> b1(stoi(choice));
        std::bitset<64> b2(stoi(message2));
        std::bitset<16> b3(stoi(message3));
        std::cout <<"Data to send choice" << b1<<"  card "<< b2<<"  pin "<< b3  << std::endl;
        std::string res = b1.to_string();
        res += b2.to_string() + b3.to_string();
        return res ;
    }

}

class UserManagerImpl : public iUserManager
{
    std::string m_card_number;
    std::string m_pin;

    std::unique_ptr<iSocket> m_socket;

    public:

    UserManagerImpl()
        :m_socket(nullptr)
    {}

    ~UserManagerImpl()
    {
        m_socket->close();
    }

    bool setCredentials(const std::string& card_number, const std::string& pin) override
    {
        m_card_number = card_number;
        m_pin = pin;

        // TODO
        return true;
    }

    bool process_registration() override
    {
        std::string mes = proc_reg;
        mes += m_card_number;
        mes += m_pin;
        std::cout<<" sent message"<< mes<<std::endl;
        int response = m_socket->sendMessage(mes);
         
        return (response > 0) ? true : false;
    }

    bool process_card() override
    {
        std::string mes = proc_card;
        mes += m_card_number;
        mes += m_pin;
        int response = m_socket->sendMessage(mes);

        if(response > 0)
        {
            return true;
        } else {
            return false;
        }
    }

    bool cash_in(int) override
    {
        return true;
    }

    bool cash_out(int) override
    {
        return true;
    }

    double get_balance() override
    {
        int response = m_socket->sendMessage(makeString("3",m_card_number,m_pin));

        if(response > 0)
        {
            return true;
        } else {
            return false;
        }
    }

    int connect_socket(std::unique_ptr<iSocket> socket) override
    {
        m_socket = std::move(socket);
        return m_socket->connect();
    }
};

std::unique_ptr<iUserManager> createUserManager()
{
    return std::unique_ptr<iUserManager>(new UserManagerImpl());
}

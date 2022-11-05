
#include "iusermanager.hpp"
#include "isocket.hpp"

#include <iostream>
#include <bitset>

namespace {

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
    const std::string m_card_number;
    const std::string m_pin;

    std::unique_ptr<iSocket> m_socket;

    public:

    UserManagerImpl(const std::string& card_number, const std::string& pin)
        : m_card_number(card_number)
        , m_pin(pin)
        , m_socket(nullptr)
    {}

    ~UserManagerImpl()
    {
        m_socket->close();
    }

    bool process_registration() override
    {
        //TODO
        m_socket->sendMessage("");
         
        
        return true;
    }

    bool process_card() override
    {
        return true;
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
        return double();
    }

    void connect_socket(std::unique_ptr<iSocket> socket) override
    {
        m_socket = std::move(socket);
        m_socket->connect();
    }
};

std::unique_ptr<iUserManager> createUserManager(const std::string& card_number, const std::string& pin)
{
    return std::unique_ptr<iUserManager>(new UserManagerImpl(card_number, pin));
}

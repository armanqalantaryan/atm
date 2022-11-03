#include <memory>

#include "iclientmanager.hpp"

class ClientManagerImpl : public iClientManager
{
    const std:string m_card_number;
   const std::string m_pin;

    public:

    ClientManagerImpl(std::string card_number, std::string pin)
        : m_card_number(card_number)
        , m_pin(pin)
    {}

    virtual bool process_registration()
    {
        return true;
    }
    virtual bool process_card()
    {
        return true;
    }
    virtual bool cash_in(int)
    {
        return true;
    }
    virtual bool cash_out(int)
    {
        return true;
    }
    virtual double get_balance()
    {
        return double();
    }
};

std::unique_ptr<iClientManager> createClientManager(std::string card_number, std::string pin)
{
    return std::unique_ptr<iClientManager>(new ClientManagerImpl(card_number, pin));
}

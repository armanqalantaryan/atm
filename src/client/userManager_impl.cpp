#include "iusermanager.hpp"
#include "isocket.hpp"

#include <iostream>
#include <cassert>

using namespace std;

namespace {

    const std::string PROCESS_REGISTRATION = "1";
    const std::string PROCESS_CARD = "2";
    const std::string get_bal = "3";
    const std::string PROCESS_CASHIN = "4";
    const std::string PROCESS_CASHOUT = "5";
    const std::string ex_msg = "6";
    const std::string OK = "1";
    const std::string NOT_OK = "2";
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

    void runAtm() override
    {

        do
        {
            cout << "New card registration, press 1" << endl;
            cout << "Enter card number, press 2" << endl;

            int choice;
            cin >> choice;
            setCredentials();

            switch (choice)
            {
                case 1 :
                {
                    if(process_registration())
                    {
                        std::cout << "Card Registered" << std::endl;
                    }
                    else
                    {
                        std::cout <<"Card Already exists. Try Another Card Number" << std::endl;
                        continue;
                    }
                }
                break;

                case 2 :
                {
                    if (process_card())
                    {
                        bool exit = false;
                        do
                        {
                            cout << endl;
                            cout << "Check balance, press 1" << endl;
                            cout << "Cash in, press 2" << endl;
                            cout << "Cash out, press 3" << endl;
                            cout << "Exit, press 4" << endl;
                            cout << endl;

                            int choice = 0;
                            cin >> choice;

                            switch (choice)
                            {
                                case 1:
                                {
                                    double balance = get_balance();
                                    cout << "Balance is: " << balance << endl;
                                }
                                break;

                                case 2:
                                {
                                    cout << "Insert amount: ";
                                    int amount;
                                    cin >> amount;
                                    bool res = cash_in(amount);
                                    if (res)
                                        cout << "Your amount is successfully set" << endl;
                                    else
                                        cout << "Failed transaction" << endl;
                                }
                                break;

                                case 3:
                                {
                                    cout << "Insert amount: ";
                                    int amount;
                                    cin >> amount;
                                    bool res = cash_out(amount);
                                    if (res)
                                        cout << "Take your cash!" << endl;
                                    else
                                        cout << "Failed transaction" << endl;
                                }
                                break;

                                case 4:
                                {
                                    exit = true;;
                                }
                            }

                        } while (!exit);

                    }
                    else
                    {
                        cout << "Invalid card number or pin, try again" << endl;
                        continue;
                    }
                }
                break;
            }

        } while(true);

    }
    void setCredentials() override
    {
        std::string card_number;
        std::string pin;
        do
        {
            cout << "Enter card number: " << endl;
            cin >> card_number;
            if (card_number.size() != 12)
            {
                cout << "Invalid card input, must be 12 symbols" << endl;
                continue;
            }
            break;
        }
        while(true);

        do
        {
            cout << "Enter pin: " << endl;
            cin >> pin;

            if (pin.size() != 4)
            {
                cout << "Invalid pin input, must be 4 symbols" << endl;
                continue;
            }

            break;

        } while(true);

        m_card_number = card_number;
        m_pin = pin;
    }

    bool process_registration() override
    {
        std::string mes = PROCESS_REGISTRATION;
        mes += m_card_number;
        mes += m_pin;
        int res = m_socket->sendMessage(mes);

        assert(res > 0);

        res = m_socket->receiveMessage(mes);
        assert(res > 0);

        return (mes == "1") ? true : false;
    }

    bool process_card() override
    {
        std::string mes = PROCESS_CARD;
        mes += m_card_number;
        mes += m_pin;
        int response = m_socket->sendMessage(mes);
        assert(response > 0);
        
        response = m_socket->receiveMessage(mes);
        assert(response > 0);

        return mes == OK ? true : false;
    }

    bool cash_in(int amount) override
    {
        std::string mes = PROCESS_CASHIN;
        mes += m_card_number;
        mes += m_pin;
        mes += to_string(amount);
        int response = m_socket->sendMessage(mes);
        assert(response > 0);
        
        response = m_socket->receiveMessage(mes);
        assert(response > 0);

        return mes == OK ? true : false;
    }

    bool cash_out(int amount) override
    {
        std::string mes = PROCESS_CASHOUT;
        mes += m_card_number;
        mes += m_pin;
        mes += to_string(amount);
        int response = m_socket->sendMessage(mes);
        assert(response > 0);

        response = m_socket->receiveMessage(mes);
        assert(response > 0);

        return mes == OK ? true : false;
    }

    double get_balance() override
    {
        std::string mes = get_bal;
        mes += m_card_number;
        mes += m_pin;
        int response = m_socket->sendMessage(mes);

        if(response < 0)
        {
            throw;
        }
        response = m_socket->receiveMessage(mes);
        std::cout << "balance is -----   " << mes << std::endl;
        if(response < 0)
        {
            throw;
        }
         return atoi(mes.c_str());
    }

    int connect_socket(std::unique_ptr<iSocket> socket) override
    {
        m_socket = std::move(socket);
        return m_socket->connect();
    }
};

std::unique_ptr<iUserManager> createUserManager()
{
    return std::make_unique<UserManagerImpl>();
}

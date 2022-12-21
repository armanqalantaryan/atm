#include <iostream>
#include <cassert>

#include "iclientusermanager.hpp"
#include "iclientsocket.hpp"

using namespace std;

namespace {

    const string PROCESS_REGISTRATION = "1";
    const string PROCESS_CARD = "2";
    const string get_bal = "3";
    const string PROCESS_CASHIN = "4";
    const string PROCESS_CASHOUT = "5";
    const string ex_msg = "6";
    const string OK = "1";
    const string NOT_OK = "2";
}

class ClientUserManagerImpl : public iClientUserManager
{
    string m_card_number;
    string m_pin;

    unique_ptr<iClientSocket> m_socket;

public:

    ClientUserManagerImpl()
        :m_socket(nullptr)
    {}

    ~ClientUserManagerImpl()
    {
        m_socket->close();
    }

    int connectSocket(std::unique_ptr<iClientSocket> socket) override
    {
        m_socket = std::move(socket);
        return m_socket->connect();
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
                    if(processRegistration())
                    {
                        std::cout << "--- Card Registered ---" << std::endl;
                    }
                    else
                    {
                        std::cout <<"--- Card Already exists. Try Another Card Number ---" << std::endl;
                        continue;
                    }
                }
                break;

                case 2 :
                {
                    if (processCard())
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
                                    double balance = getBalance();
                                    cout << "--- Balance is: --- " << balance << endl;
                                }
                                break;

                                case 2:
                                {
                                    cout << "Insert amount: ";
                                    int amount;
                                    cin >> amount;
                                    bool res = cashIn(amount);
                                    if (res)
                                        cout << "--- Your amount is successfully set ---" << endl;
                                    else
                                        cout << "--- Failed transaction ---" << endl;
                                }
                                break;

                                case 3:
                                {
                                    cout << "Insert amount: ";
                                    int amount;
                                    cin >> amount;
                                    bool res = cashOut(amount);
                                    if (res)
                                        cout << "--- Take your cash! ---" << endl;
                                    else
                                        cout << "--- Not enough amount ---" << endl;
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
                        cout << "--- Invalid card number or pin, try again ---" << endl;
                        continue;
                    }
                }
                break;
            }

        } while(true);

    }

private:

    void setCredentials()
    {
        std::string card_number;
        std::string pin;
        do
        {
            cout << "Enter card number: " << endl;
            cin >> card_number;
            if (card_number.size() != 12)
            {
                cout << "--- Invalid card input, must be 12 symbols ---" << endl;
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
                cout << "--- Invalid pin input, must be 4 symbols ---" << endl;
                continue;
            }

            break;

        } while(true);

        m_card_number = card_number;
        m_pin = pin;
    }

    bool processRegistration()
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

    bool processCard()
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

    bool cashIn(int amount)
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

    bool cashOut(int amount)
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

    double getBalance()
    {
        std::string mes = get_bal;
        mes += m_card_number;
        mes += m_pin;
        int response = m_socket->sendMessage(mes);

        if(response < 0)
        {
            assert(false);
        }
        response = m_socket->receiveMessage(mes);
        if(response < 0)
        {
            assert(false);
        }
        return atoi(mes.c_str());
    }
};

std::unique_ptr<iClientUserManager> createClientUserManager()
{
    return std::make_unique<ClientUserManagerImpl>();
}

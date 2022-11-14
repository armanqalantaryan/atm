#include <iostream>
#include <memory>

#include "iusermanager.hpp"
#include "isocket.hpp"

using namespace std;

unique_ptr<iUserManager> createUserManager();
std::unique_ptr<iSocket> createSocket();

int main()
{
    unique_ptr<iUserManager> um = createUserManager();

    if (um->connect_socket(createSocket()) == -1)
    {
        cout << "Internal server error" << endl;
        return -1;
    }

    do
    {
        cout << "New card registration, press 1" << endl;
        cout << "Enter card number, press 2" << endl;

        int choice;
        cin >> choice;

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

        if (!um->setCredentials(card_number, pin))
        {
            cout << "Invalid credentials, try again " << endl;
            continue;
        }

        switch (choice)
        {
            case 1 :
                {
                    std::cout << " choice 1" << std::endl;
                    if (um->process_registration())
                    {
                    }
                    else
                    {
                    }
                }

                break;

            case 2 :
                {
                    if (um->process_card())
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

                            int choice;
                            cin >> choice;

                            switch (choice)
                            {
                                case 1:

                                    {
                                        double balance = um->get_balance();
                                        cout << "Balance is: " << balance << endl;
                                    }

                                    break;

                                case 2:
                                    {
                                        cout << "Insert amount: "; 
                                        int amount;
                                        cin >> amount;
                                        bool res =  um->cash_in(amount);
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
                                        bool res =  um->cash_out(amount);
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
                        cout << "Failed to process card" << endl;
                    }
                }
        }
        
    } while(true);


    return 0;
}

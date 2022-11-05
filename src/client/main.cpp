#include <iostream>
#include <memory>

#include "iusermanager.hpp"
#include "isocket.hpp"

using namespace std;

unique_ptr<iUserManager> createUserManager(const std::string& card_number, const std::string& pin);
std::unique_ptr<iSocket> createSocket();

int main()
{
    unique_ptr<iSocket> socket = createSocket();
    socket->connect();
    do
    {
        cout << "New card registration, press 1" << endl;
        cout << "Enter card number, press 2" << endl;

        int choice;
        cin >> choice;

        std::string card_number;
        cout << "Enter card number: " << endl;
        cin >> card_number;

        cout << "Enter pin: " << endl;
        std::string pin;
        cin >> pin;
        unique_ptr<iUserManager> cm = createUserManager(card_number, pin);
        
        cm->connect_socket(createSocket());

        switch (choice)
        {
            case 1 :
                {

                    if (cm->process_registration())
                    {
                    }
                    else
                    {
                    }
                }

                break;

            case 2 :
                {
                    if (cm->process_card())
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
                                        double balance = cm->get_balance();
                                        cout << "Balance is: " << balance << endl;
                                    }

                                    break;

                                case 2:
                                    {
                                        cout << "Insert amount: "; 
                                        int amount;
                                        cin >> amount;
                                        bool res =  cm->cash_in(amount);
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
                                        bool res =  cm->cash_out(amount);
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

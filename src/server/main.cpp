#include <iostream>
#include <memory>

#include "iusermanager.hpp"

std::unique_ptr<iSocket> createSocket();
std::unique_ptr<iUserManager> createUserManager();

int main()
{
    std::unique_ptr<iUserManager> um = createUserManager();
    if(!um->connect_socket(createSocket()))
    {
        std::cerr<<"Connection Error" <<std::endl;
    }

    std::string str = "";
    while(true)
    {
        while(um->receiveMessage(str)) 
        {
            std::cout << "************ Received **********" << str << std::endl;
            break;
        }
    }

}

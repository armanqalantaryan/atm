#include <iostream>
#include <memory>

#include "iusermanager.hpp"


std::unique_ptr<iSocket> createSocket();
std::unique_ptr<iDb> createDb();
std::unique_ptr<iUserManager> createUserManager();


int main()
{
    std::unique_ptr<iUserManager> um = createUserManager();
    if(!um->connect_socket(createSocket()))
    {
        std::cerr<<"Connection Error" <<std::endl;
    }

    if(!um->connect_db(createDb()))
    {
        std::cerr<<"Database Error" <<std::endl;
    }

    while(true)
    {
        um->processMessage();
    }
}

#include <iostream>
#include <memory>

#include "iusermanager.hpp"


std::unique_ptr<iSocket> createSocket();
std::unique_ptr<iSqlDB> createDb();
std::unique_ptr<iUserManager> createUserManager();


int main()
{
    std::unique_ptr<iUserManager> um = createUserManager();
    if(!um->connect_socket(createSocket()))
    {
        std::cerr<<"Connection Error" <<std::endl;
        return -1;
    }

    if(!um->connect_db(createDb()))
    {
        std::cerr<<"Database Error" <<std::endl;
        return -1;
    }

    um->startServer();
}

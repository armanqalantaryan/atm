#include <iostream>
#include <memory>

#include "iserverusermanager.hpp"


std::unique_ptr<iServerSocket> createServerSocket();
std::unique_ptr<iServerUserManager> createServerUserManager();
std::unique_ptr<iSqlDB> createDb();

int main()
{
    std::unique_ptr<iServerUserManager> sum = createServerUserManager();
    if(!sum->connectSocket(createServerSocket()))
    {
        std::cerr<<"Connection Error" <<std::endl;
        return -1;
    }

    if(!sum->connectDb(createDb()))
    {
        std::cerr<<"Database Error" <<std::endl;
        return -1;
    }

    sum->startServer();
}

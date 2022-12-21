#include <iostream>

#include "iclientusermanager.hpp"
#include "iclientsocket.hpp"

std::unique_ptr<iClientUserManager> createClientUserManager();
std::unique_ptr<iClientSocket> createClientSocket();

int main()
{
    std::unique_ptr<iClientUserManager> cum = createClientUserManager();

    if (cum->connectSocket(createClientSocket()) == -1)
    {
        std::cerr << "Internal server error" << std::endl;
        return -1;
    }
    cum->runAtm();
    return 0;
}

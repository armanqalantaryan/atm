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
        cerr << "Internal server error" << endl;
        return -1;
    }
    um -> runAtm();
    return 0;
}

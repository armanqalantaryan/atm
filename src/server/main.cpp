#include "isocket.hpp"
#include <iostream>

std::unique_ptr<SocketImpl> createSocket(const int& );

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cout << "Port is missing in arguments!" << std::endl;
    }
    const int port = atoi(argv[1]);

    unique_ptr<iSocket> socket = createSocket(port);


}

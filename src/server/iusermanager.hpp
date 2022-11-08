//
// Created by arman on 11/4/22.
//
#include <string>
#include <memory>

#include "isocket.hpp"

class iUserManager
{
public:
    virtual bool cardRegistration() = 0;
    virtual bool cardCheck() = 0;
    virtual bool receiveMessage(std::string&) = 0;
    virtual bool connect_socket(std::unique_ptr<iSocket> socket) = 0;
};

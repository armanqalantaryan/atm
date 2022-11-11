//
// Created by arman on 11/4/22.
//
#include <memory>

#include "isocket.hpp"
#include "idb.hpp"

class iUserManager
{
public:
    virtual void processMessage() = 0;
    virtual bool connect_socket(std::unique_ptr<iSocket> socket) = 0;
    virtual bool connect_db(std::unique_ptr<iDb> db) = 0;
};

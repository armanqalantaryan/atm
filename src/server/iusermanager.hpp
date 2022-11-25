#include <memory>

#include "isocket.hpp"
#include "isqldb.hpp"

class iUserManager
{
public:
    virtual void startServer() = 0;
    virtual bool connect_socket(std::unique_ptr<iSocket> socket) = 0;
    virtual bool connect_db(std::unique_ptr<iSqlDB> db) = 0;
};

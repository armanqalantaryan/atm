#include <memory>

#include "iserversocket.hpp"
#include "isqldb.hpp"

class iServerUserManager
{
public:
    virtual void startServer() = 0;
    virtual bool connectSocket(std::unique_ptr<iServerSocket>) = 0;
    virtual bool connectDb(std::unique_ptr<iSqlDB>) = 0;
};

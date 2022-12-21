#include <memory>

class iClientSocket;

class iClientUserManager
{
public:
    virtual int connectSocket(std::unique_ptr<iClientSocket>) = 0;
    virtual void runAtm() = 0;
};

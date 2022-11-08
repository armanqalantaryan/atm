#include <string>

class iSocket {
public:
    virtual int bind() = 0;
    virtual void listen() = 0;
    virtual int accept() = 0;

    virtual int sendMessage(const std::string&) = 0;
    virtual int receiveMessage(char*) = 0;

    virtual void close() = 0;
};

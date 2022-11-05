
class iSocket {
public:
    virtual bool connect() = 0;
    virtual void close() = 0;
    virtual bool receiveMessage() = 0;
    virtual int sendMessage(const std::string&) = 0;
};

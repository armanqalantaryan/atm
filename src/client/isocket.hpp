
class iSocket {
public:
    void virtual connectSocket() = 0;
    void virtual closeSocket() = 0;
    bool virtual receiveMessage() = 0;
    bool virtual sendMessage(std::string&) = 0;
    const std::string virtual makeString(const std::string& choice, const std::string&, const std::string&) = 0;
};

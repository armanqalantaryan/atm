#include <string>

class iDb
{
public:
    virtual bool write (const std::string&, const std::string&) = 0;
    virtual std::string read () = 0;
    virtual bool init() = 0;
};

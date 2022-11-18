#include <vector>

class iSqlDB
{
public:

    virtual bool connect(const std::string& dbName) = 0;
    virtual bool close() = 0;
    virtual std::pair<std::vector<std::vector<std::string>>, int> runSql(const std::string& sql) = 0;
};

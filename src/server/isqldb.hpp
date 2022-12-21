#include <vector>

typedef std::pair<std::vector<std::vector<std::string>>, int> SQL_TABLE;

class iSqlDB
{
public:

    virtual bool connect(const std::string& dbName) = 0;
    virtual bool close() = 0;
    virtual SQL_TABLE runSql(const std::string& sql) = 0;
};

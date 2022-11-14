#include <iostream>
#include <memory>
#include <string>
#include "sqlite3.h"

#include "idb.hpp"

class DbImpl: public iDb
{
    sqlite3* m_db;

public:

    bool init() override
    {
        int rc;
        char* Errmsg = 0;
        rc = sqlite3_open("atm.db", &m_db);
        if(rc)
        {
            std::cerr << "Can`t open database "<< std::endl << sqlite3_errmsg(m_db);
            return false;
        }
        else
        {
            std::cout << "Opened database successfully" << std::endl;
        }

        std::string sql = "create table if not exists user("    \
          " card_number TEXT  not null,"           \
          " pin TEXT not null,"                             \
          " balance TEXT not null"                               \
          ");";

        rc = sqlite3_exec(m_db, sql.c_str(), nullptr, 0, &Errmsg);
        std::cout<< "INIT code ******" << rc <<std::endl;

        return (rc == 0) ? true : false;
    }

    int readCallback(void* data, int argc, char** argv,char** ColName)
    {
        return 0;
    }

    bool write(const std::string& identifier, const std::string& value) override
    {
        char* Errmsg = 0;
        int rc;
        std::string sql = "INSERT INTO user (card_number, pin, balance) "  \
              "VALUES (";
        sql += "'" + identifier + "',";
        sql += "'" + value + "',";
        sql += "'0' """")" ;

        std::cout<< "*** SQL code ******" << sql <<std::endl;

        rc = sqlite3_exec(m_db, sql.c_str(), nullptr, 0, &Errmsg);
        std::cout<< "write code ******" << rc <<std::endl;
        return (rc == 0) ? true : false;
    }

    std::string read(const std::string& identifier) override
    {
        char* Errmsg = 0;
        int rc;
        std::string sql = "SELECT  FROM user (card_number, pin, balance) "  \
              "VALUES ('124587555555', '2222', '0' ); ";
        rc = sqlite3_exec(m_db, sql.c_str(), nullptr, 0, &Errmsg);
        std::cout<< "write code ******" << rc <<std::endl;

        return std::string();
    }
};

std::unique_ptr<iDb> createDb()
{
    return std::unique_ptr<iDb>(new DbImpl());
}

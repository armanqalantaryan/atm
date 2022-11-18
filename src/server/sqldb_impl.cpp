#include <iostream>
#include <memory>
#include <functional>

#include "sqlite3.h"

#include "isqldb.hpp"
#include "utilities.hpp"

namespace 
{
    std::vector<std::vector<std::string>> sql_result_table;
}

class SqlDBImpl: public iSqlDB
{
    sqlite3* m_db;

public:

    bool connect(const std::string& dbName) override
    {
        int rc = sqlite3_open(dbName.c_str(), &m_db);
        if(rc)
        {
            std::cerr << "Can`t open database "<< std::endl << sqlite3_errmsg(m_db);
            return false;
        }

        std::cout << "Opened database successfully" << std::endl;

        return true;
    }

    bool close() override
    {
        /*int rc = sqlite3_close(dbName, &m_db);
        if(rc)
        {
            std::cerr << "Can`t open database "<< std::endl << sqlite3_errmsg(m_db);
            return false;
        }*/

        return true;

    }

    static int runSqlCallback(void * data, int argc, char** argv, char** Colname)
    {
        sql_result_table.push_back(std::vector<std::string>());
        auto table = sql_result_table.back();
        for(int i = 0; i < argc; i++)
        {
            table.push_back(argv[i]);
        }
        return 0;
    }

    std::pair<std::vector<std::vector<std::string>>, int> runSql(const std::string& sql) override
    {
        std::cout << "** RUN SQL *** " << sql << std::endl;
        char* Errmsg = 0;
        const int  rc = sqlite3_exec(m_db,sql.c_str(), runSqlCallback , 0, &Errmsg);
        
        if(rc != 0)
        {
            return {{},rc};
        }

        return std::pair<std::vector<std::vector<std::string>>, int>(move(sql_result_table), rc);
    }
};


std::unique_ptr<iSqlDB> createDb()
{
    return std::unique_ptr<iSqlDB>(new SqlDBImpl());
}

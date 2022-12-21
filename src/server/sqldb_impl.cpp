#include <iostream>
#include <memory>
#include <functional>
#include <cassert>

#include "sqlite3.h"
#include "isqldb.hpp"

namespace 
{
    std::vector<std::vector<std::string>> sql_result_table;

    int runSqlCallback(void * data, int argc, char** argv, char** Colname)
    {
        assert(argc != 0);

        sql_result_table.push_back(std::vector<std::string>());
        for(int i = 0; i < argc; i++)
        {
            sql_result_table.back().push_back(argv[i]);
        }

        return 0;
    }
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
        int rc = sqlite3_close(m_db);
        if(rc)
        {
            std::cerr << "Can`t open database "<< std::endl << sqlite3_errmsg(m_db);
            return false;
        }

        return true;
    }

    SQL_TABLE runSql(const std::string& sql) override
    {
        std::cout << "** RUN SQL *** " << sql << std::endl;
        char* Errmsg = 0;
        const int  rc = sqlite3_exec(m_db,sql.c_str(), runSqlCallback , 0, &Errmsg);
        
        if(rc != 0)
        {
            return {{},rc};
        }
        std::cout<< "sql ended normally" << std::endl;
        return SQL_TABLE(move(sql_result_table), rc);
    }
};


std::unique_ptr<iSqlDB> createDb()
{
    return std::unique_ptr<iSqlDB>(new SqlDBImpl());
}

#include <vector>

template<class ...Args>
std::string makeSql(Args ...args)
{
    std::string query = "";
    std::vector<std::string> vec = {args...};
    for(auto item : vec)
    {
        query += item;
        query += " ";
    }
    query += ';';
    return query;
}


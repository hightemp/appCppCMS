
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <unordered_map>
#include <memory>
#include <string>
#include <stdarg.h>
#include <sstream>
#include <algorithm>

#include "main.hpp"

typedef std::unique_ptr<sql::ResultSet> PResultSet;
typedef std::unique_ptr<sql::Statement> PStatement;
typedef std::unique_ptr<sql::Connection> PConnection;

struct Connection
{
    std::string sName;
    std::string sURL;
    std::string sUser;
    std::string sPassword;
    std::string sDatabase;
    PConnection poConnection;
};

class Database
{
    public:
        std::unordered_map<std::string, Connection> oConnections;
        sql::Driver* poDriver;
        std::string sCurrentConnetionName;
        
        Database();
        ~Database();
        
        void fnCreateConnection(
            std::string sName, 
            std::string sURL, 
            std::string sUser,
            std::string sPassword,
            std::string sDatabase
        );
        
        std::string fnFormatQuery(std::string sQuery, ...);
        
        void fnQuery(std::string sQuery);
        
        template<typename... Args>
        void fnQueryF(std::string sQuery, Args... pArguments)
        {
            this->fnQuery(this->fnFormatQuery(sQuery, pArguments...));
        }
        
        PResultSet fnGetRows(std::string sQuery);
        
        template<typename... Args>
        PResultSet fnGetRowsF(std::string sQuery, Args... pArguments)
        {
            return this->fnGetRows(this->fnFormatQuery(sQuery, pArguments...));
        }

        std::string fnGetField(std::string sQuery);
        template<typename... Args>
        std::string fnGetFieldF(std::string sQuery, Args... pArguments)
        {
            return this->fnGetField(this->fnFormatQuery(sQuery, pArguments...));
        }
};

#endif
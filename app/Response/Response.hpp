
#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <string>

#include "View.hpp"

class Response
{
    std::string sContent;
    std::unordered_map<std::string, std::string> oHeaders;
    
    public:
        std::string fnGetOutput();
        void fnFlush();
        std::string fnGetHeader(std::string sHeaderName);
        void fnSetHeader(std::string sHeaderName, std::string sContent);
        std::string fnGetContent();
        void fnSetContent(std::string sContent);
        void fnSetContent(View oView);

        Response();
        ~Response();
};

#endif
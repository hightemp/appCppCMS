
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>
#include <cgicc/Cgicc.h>
#include <stdexcept>

#include "Types.hpp"

class Application;

class Request
{
    Application *oApplication;
    cgicc::Cgicc oCGI;
    
    public:
        Request(Application *oApplication): 
            oApplication(oApplication)
        {
            
        }
        ~Request();
        
        bool fnIsExist(std::string sVarName);
        std::string fnGetString(std::string sVarName);
        int fnGetInt(std::string sVarName);
        
        bool fnIsPost();
        bool fnIsGet();
        std::string fnGetMethod();
        std::vector<std::string> &fnGetVarNames();
};

#endif
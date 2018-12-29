
#include "Application.hpp"

#include "Request.hpp"

Request::~Request()
{
    
}

bool Request::fnIsExist(std::string sVarName)
{
    return this->oCGI.getElements().end() != this->oCGI.getElement(sVarName);
}

std::string Request::fnGetString(std::string sVarName)
{
    return this->oCGI(sVarName);
}

int Request::fnGetInt(std::string sVarName)
{
    return std::stoi(this->fnGetString(sVarName));
}

bool Request::fnIsPost()
{
    return this->oApplication->oEnvironmentVars["REQUEST_METHOD"] == "POST";
}

bool Request::fnIsGet()
{
    return this->oApplication->oEnvironmentVars["REQUEST_METHOD"] == "GET";
}

std::string Request::fnGetMethod()
{
    return this->oApplication->oEnvironmentVars["REQUEST_METHOD"];
}

std::vector<std::string> &Request::fnGetVarNames()
{
    static bool bInit = false;
    static std::vector<std::string> oVarNames;
    
    if (!bInit) {
        for(cgicc::const_form_iterator oIterator = this->oCGI.getElements().begin(); 
            oIterator != this->oCGI.getElements().end(); 
            ++oIterator) {
            oVarNames.push_back(oIterator->getName());
        }
        bInit = true;
    }
    
    return oVarNames;
}
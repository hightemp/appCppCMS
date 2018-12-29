
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
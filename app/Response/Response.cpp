
#include "Response.hpp"

Response::Response()
{
    this->oHeaders["Content-type"] = "text/html";
}

Response::~Response()
{
    
}

std::string Response::fnGetOutput()
{
    std::string sHeaders;
    
    for (TStringStringPair oPair : oHeaders) {
        sHeaders += oPair.first + ":" + oPair.second + "\r\n";
    }
    
    sHeaders += "\r\n";
    
    return sHeaders + this->sContent;
}

void Response::fnFlush()
{
    std::cout << this->fnGetOutput();
}

std::string Response::fnGetHeader(std::string sHeaderName)
{
    return this->oHeaders[sHeaderName];
}

void Response::fnSetHeader(std::string sHeaderName, std::string sContent)
{
    this->oHeaders[sHeaderName] = sContent;
}

std::string Response::fnGetContent()
{
    return this->sContent;
}

void Response::fnSetContent(std::string sContent)
{
    this->sContent = sContent;
}

void Response::fnSetContent(View oView)
{
    this->sContent = oView.fnGetContent();
}
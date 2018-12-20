
#include "View.hpp"

View::View()
{
    this->oBuffers["Main"] = "";
    
    this->oBufferStack.push_back("Main");
}

View::~View()
{
    
}

std::string View::fnGetContent()
{
    return this->oBuffers["Main"];
}

void View::fnFlush()
{
    std::cout << this->fnGetContent();
}

void View::fnStartBuffer(std::string sName)
{
    for (std::string &sBufferName : this->oBufferStack) {
        if (sBufferName==sName) {
            std::runtime_error("Buffer already in usage");
        }
    }
    
    if (this->oBuffers.find(sName)==this->oBuffers.end()) {
        this->oBuffers[sName] = "";
    }
    
    this->oBufferStack.push_back(sName);
}

void View::fnEndBuffer()
{
    if (this->oBufferStack.size()>1) {
        this->oBufferStack.pop_back();
    }
}

std::string View::fnGetBufferContents()
{
    return this->oBuffers[this->fnGetCurrentBufferName()];
}

void View::fnCleanBuffer()
{
    this->oBuffers[this->fnGetCurrentBufferName()] = "";
}

void View::fnFlushBuffer()
{
    std::cout << this->oBuffers[this->fnGetCurrentBufferName()];
}

void View::fnWriteToBuffer(std::string sString)
{
    this->oBuffers[this->fnGetCurrentBufferName()] += sString;
}

void View::fnSetBufferContents(std::string sString)
{
    this->oBuffers[this->fnGetCurrentBufferName()] = sString;
}

std::string View::fnGetCurrentBufferName()
{
    return this->oBufferStack.back();
}
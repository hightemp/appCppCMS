
#include "Logger.hpp"

Logger::Logger()
{
    oFileBuf.open ("test.log", std::ios::out);
    //this->cLogLevel = 
}

Logger::~Logger()
{
    oFileBuf.close();
}

void Logger::fnLog(std::string sString, char cLogLevel)
{
    if (this->cLogLevel<cLogLevel) {
        return;
    }
    
    std::ostream oOStream(&oFileBuf);
    
    time_t oRawTime;
    
    time(&oRawTime);
    
    oOStream << ctime(&oRawTime) << sString << std::endl;
}

void Logger::fnWarning(std::string sString, char cLogLevel)
{
    this->fnLog(" [W] "+sString, cLogLevel);
}

void Logger::fnError(std::string sString, char cLogLevel)
{
    this->fnLog(" [E] "+sString, cLogLevel);
}

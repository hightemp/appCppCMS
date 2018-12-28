
#include "Logger.hpp"

void Logger::fnInitialize(std::string sLogFileName, char cLogLevel)
{
    std::string sFilePath = FileSystem::fnGetFullPath(sLogFileName);
    
    oFileBuf.open(sFilePath, std::ios::out);
    
    this->cLogLevel = cLogLevel;
}

Logger::Logger(std::string sLogFileName, char cLogLevel)
{
    this->fnInitialize(
        sLogFileName,
        cLogLevel
    );
}

Logger::Logger(Configuration *oConfiguration)
{
    this->fnInitialize(
        oConfiguration->fnGetString("sLogFilePath", "logger.log"),
        oConfiguration->fnGetInt("cLogLevel", 3)
    );
}

Logger::~Logger()
{
    oFileBuf.close();
}

void Logger::fnLog(std::string sString, char cLogLevel)
{
    if (!oFileBuf.is_open()) {
        return;
    }
    
    if (this->cLogLevel<cLogLevel) {
        return;
    }
    
    std::ostream oOStream(&oFileBuf);
    
    char caStrTime[20];
    time_t oRawTime = time(NULL);
    struct tm * pRawTime = localtime(&oRawTime);

    strftime(caStrTime, 20, "%F %X", pRawTime);
    
    oOStream << caStrTime << " " << sString << std::endl;
}

void Logger::fnWarning(std::string sString, char cLogLevel)
{
    this->fnLog("[W] "+sString, cLogLevel);
}

void Logger::fnError(std::string sString, char cLogLevel)
{
    this->fnLog("[E] "+sString, cLogLevel);
}

void Logger::fnLogF(std::string sString, char cLogLevel, ...)
{
    char caBuffer[255];
    va_list pArglist;
    
    va_start(pArglist, cLogLevel);
    vsprintf(caBuffer, sString.c_str(), pArglist);
    va_end(pArglist);
    
    this->fnLog(caBuffer, cLogLevel);
}

void Logger::fnWarningF(std::string sString, char cLogLevel, ...)
{
    char caBuffer[255];
    va_list pArglist;
    
    va_start(pArglist, cLogLevel);
    vsprintf(caBuffer, sString.c_str(), pArglist);
    va_end(pArglist);
    
    this->fnWarning(caBuffer, cLogLevel);
}

void Logger::fnErrorF(std::string sString, char cLogLevel, ...)
{
    char caBuffer[255];
    va_list pArglist;
    
    va_start(pArglist, cLogLevel);
    vsprintf(caBuffer, sString.c_str(), pArglist);
    va_end(pArglist);
    
    this->fnError(caBuffer, cLogLevel);
}

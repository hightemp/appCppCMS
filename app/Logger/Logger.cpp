
#include "Logger.hpp"

void Logger::fnInitialize(std::string sLogFileName, char cLogLevel)
{
    char aCurrentDir[FILENAME_MAX];
    
    getcwd(aCurrentDir, FILENAME_MAX);
    
    std::string sCurrentDir(aCurrentDir);
    
    std::string sFilePath;
    
    if (sLogFileName[0]=='/') {
        sFilePath = sLogFileName;
    } else {
        sFilePath = sCurrentDir + sLogFileName;
    }
    
    oFileBuf.open(sFilePath, std::ios::out);
    
    this->cLogLevel = cLogLevel;
}

Logger::Logger(std::string sLogFileName, char cLogLevel)
{
    std::cout << "Logger::Logger(std::string sLogFileName, char cLogLevel)\n";
    
    this->fnInitialize(
        sLogFileName,
        cLogLevel
    );
}

Logger::Logger()
{
    std::cout << "Logger::Logger()\n";

    this->fnInitialize(
        oConfiguration.fnGetString("sLogFilePath", "test.log"),
        oConfiguration.fnGetInt("cLogLevel", 3)
    );
}

Logger::~Logger()
{
    std::cout << "Logger::~Logger()\n";
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

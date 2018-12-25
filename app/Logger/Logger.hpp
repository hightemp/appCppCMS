
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>

#include "main.hpp"

class Logger
{
    std::filebuf oFileBuf;
    char cLogLevel = 0;
    
    void fnInitialize(std::string sLogFileName, char cLogLevel);
    
    public:
    
        Logger(std::string sLogFileName, char cLogLevel);
        Logger();
        ~Logger();
        
        void fnLog(std::string sString, char cLogLevel);
        void fnWarning(std::string sString, char cLogLevel);
        void fnError(std::string sString, char cLogLevel);
        void fnLogF(std::string sString, char cLogLevel, ...);
        void fnWarningF(std::string sString, char cLogLevel, ...);
        void fnErrorF(std::string sString, char cLogLevel, ...);
};

#endif
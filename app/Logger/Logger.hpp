
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdexcept>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>

#include "Configuration.hpp"
#include "FileSystem.hpp"

class Logger
{
    std::filebuf oFileBuf;
    char cLogLevel = 0;
    
    void fnInitialize(std::string sLogFileName, char cLogLevel);
    
    public:
    
        Logger(std::string sLogFileName, char cLogLevel);
        Logger(Configuration *oConfiguration);
        ~Logger();
        
        void fnLog(std::string sString, char cLogLevel);
        void fnWarning(std::string sString, char cLogLevel);
        void fnError(std::string sString, char cLogLevel);
        void fnLogF(std::string sString, char cLogLevel, ...);
        void fnWarningF(std::string sString, char cLogLevel, ...);
        void fnErrorF(std::string sString, char cLogLevel, ...);
};

#endif

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

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
        
        void fnLog(std::string sString, char cLogLevel=0);
        void fnWarning(std::string sString, char cLogLevel=0);
        void fnError(std::string sString, char cLogLevel=0);
};

#endif
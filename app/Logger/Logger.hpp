
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <time.h>

class Logger
{
    std::filebuf oFileBuf;
    char cLogLevel = 0;
    
    public:
    
        Logger();
        ~Logger();
        
        void fnLog(std::string sString, char cLogLevel=0);
        void fnWarning(std::string sString, char cLogLevel=0);
        void fnError(std::string sString, char cLogLevel=0);
};

#endif
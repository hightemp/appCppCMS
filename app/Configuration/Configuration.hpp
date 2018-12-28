
#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <iostream>
#include <fstream>
#include <cstdio>

#include "Types.hpp"
#include "Logger.hpp"

class Logger;

struct ConfigurationNode
{
    char cType;
    ConfigurationNode(char cType) : cType(cType) {};
};

struct ConfigurationStringNode : public ConfigurationNode
{
    std::string sValue;
    
    ConfigurationStringNode() : ConfigurationNode(1) {};
};

struct ConfigurationIntNode : public ConfigurationNode
{
    int iValue;

    ConfigurationIntNode() : ConfigurationNode(2) {};
};

class Configuration
{
    TStringConfigurationNodeUnorderedMap oStore;
    bool bIsLoaded = false;
    Logger *oErrorLogger;
    
    public:
        Configuration(Logger *oErrorLogger);
        ~Configuration();
        
        void fnLoadFile(std::string sFileName);
        
        void fnSetString(std::string sKey, std::string sValue);
        std::string fnGetString(std::string sKey, std::string sDefaultValue="");
        void fnSetInt(std::string sKey, int iValue);
        int fnGetInt(std::string sKey, int iDefaultValue);
        
        bool fnIsLoaded();
};

#endif
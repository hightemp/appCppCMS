
#include "Configuration.hpp"

Configuration::Configuration()
{
    this->fnLoadFile("config.cfg");
}

Configuration::~Configuration()
{
    
}

void Configuration::fnLoadFile(std::string sFileName)
{
    std::filebuf oFileBuf;
    
    oFileBuf.close();
}

void Configuration::fnSetString(std::string sKey, std::string sValue)
{
    this->oStore[sKey].reset(new ConfigurationStringNode);
    
    this->oStore[sKey]->sValue = sValue
}

std::string Configuration::fnGetString(std::string sKey, std::string sDefaultValue)
{
    return this->oStore[sKey]->sValue;
}
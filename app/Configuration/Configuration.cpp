
#include "Configuration.hpp"

Configuration::Configuration()
{
    std::cout << "Configuration::Configuration()\n";
    this->fnLoadFile("config.cfg");
}

Configuration::~Configuration()
{
    std::cout << "Configuration::~Configuration()\n";
}

void Configuration::fnLoadFile(std::string sFileName)
{
    std::filebuf oFileBuf;
    
    if (!oFileBuf.is_open()) {
        oErrorLogger.fnLog("Configuration file did not open");
        return;
    }
    
    while (oFileBuf.snextc() != EOF) {
      char cChar = oFileBuf.sgetc();
      std::cout << cChar << std::endl;
    } 
    
    oFileBuf.close();
}

void Configuration::fnSetString(std::string sKey, std::string sValue)
{
    std::cout << "Configuration::fnSetString(std::string sKey, std::string sValue)\n";
    return;
    this->oStore[sKey].reset(new ConfigurationStringNode);
    
    ((ConfigurationStringNode *) this->oStore[sKey].get())->sValue = sValue;
}

std::string Configuration::fnGetString(std::string sKey, std::string sDefaultValue)
{
    std::cout << "Configuration::fnGetString(std::string sKey, std::string sDefaultValue)\n";
    //return std::string("");
    if (this->oStore.find(sKey) == this->oStore.end()) {
        return sDefaultValue;
    }
    return  ((ConfigurationStringNode *) this->oStore[sKey].get())->sValue;
}

void Configuration::fnSetInt(std::string sKey, int iValue)
{
    this->oStore[sKey].reset(new ConfigurationIntNode);
    
    ((ConfigurationIntNode *) this->oStore[sKey].get())->iValue = iValue;
}

int Configuration::fnGetInt(std::string sKey, int iDefaultValue)
{
    if (this->oStore.find(sKey) == this->oStore.end()) {
        return iDefaultValue;
    }
    return  ((ConfigurationIntNode *) this->oStore[sKey].get())->iValue;
}
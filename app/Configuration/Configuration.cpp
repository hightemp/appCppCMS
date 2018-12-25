
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
    
    if (!oFileBuf.is_open()) {
        oErrorLogger.fnErrorF("Configuration file %s did not open", 0, sFileName.c_str());
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
    this->oStore[sKey].reset(new ConfigurationStringNode);
    
    ((ConfigurationStringNode *) this->oStore[sKey].get())->sValue = sValue;
}

std::string Configuration::fnGetString(std::string sKey, std::string sDefaultValue)
{
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
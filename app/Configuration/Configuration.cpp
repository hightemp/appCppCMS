
#include "Configuration.hpp"

Configuration::Configuration(Logger *oErrorLogger)
{
    this->oErrorLogger = oErrorLogger;
    this->fnLoadFile("config.cfg");
}

Configuration::~Configuration()
{
    
}

void Configuration::fnLoadFile(std::string sFileName)
{
    std::filebuf oFileBuf;
    std::string sFilePath = FileSystem::fnGetFullPath(sFileName);
    
    oFileBuf.open(sFilePath, std::ios::in);
    
    if (!oFileBuf.is_open()) {
        this->oErrorLogger->fnErrorF("Configuration file '%s' did not open", 0, sFilePath.c_str());
        this->bIsLoaded = false;
        return;
    }
    
    bool bStringFlag = false;
    bool bFloatFlag = false;
    bool bIntFlag = false;
    bool bNumberFlag = false;
    bool bVarNameFlag = false;
    bool bVarValueFlag = false;

    std::string sVarName;
    std::string sVarValue;
    char cStringQuote = 0;
    int iLineNumber = 1;
    
    while (oFileBuf.in_avail() > 0) {
        char cChar = oFileBuf.sgetc();
      
        if (bVarValueFlag) {
            if (bStringFlag) {
                if (cChar==cStringQuote) {
                    this->fnSetString(sVarName, sVarValue);
                    bStringFlag = false;
                    bVarValueFlag = false;
                } else {
                    sVarValue += cChar;
                }
            } else if (bNumberFlag) {
                if (cChar=='.') {
                    bFloatFlag = true;
                    bIntFlag = false;
                    sVarValue += cChar;
                } else if (cChar>='0' && cChar<='9') {
                    sVarValue += cChar;
                } else {
                    if (bIntFlag) {
                        this->fnSetInt(sVarName, std::stoi(sVarValue, nullptr, 0));
                    }
                    bFloatFlag = false;
                    bIntFlag = false;
                    bNumberFlag = false;
                    bVarValueFlag = false;
                }
            } else {
                if (cChar==' ') {
                    
                } else if (cChar>='0' && cChar<='9') {
                    bNumberFlag = true;
                    bIntFlag = true;
                    bFloatFlag = false;
                    sVarValue += cChar;
                } else if (cChar=='.') {
                    bNumberFlag = true;
                    bIntFlag = false;
                    bFloatFlag = true;
                    sVarValue += cChar;
                } else if (cChar=='"' || cChar=='\'') {
                    cStringQuote = cChar;
                    bStringFlag = true;
                }
            }
        } else {
            if (!bVarNameFlag) {
                if ((cChar>='a' && cChar<='z') || (cChar>='A' && cChar<='Z') || (cChar>='0' && cChar<='9')) {
                    sVarName += cChar;
                    bVarNameFlag = true;
                }
            } else {
                if ((cChar>='a' && cChar<='z') || (cChar>='A' && cChar<='Z') || (cChar>='0' && cChar<='9')) {
                    sVarName += cChar;
                } else {
                    if (cChar=='=') {
                        bVarNameFlag = false;
                        bVarValueFlag = true;
                    } else if (cChar==' ') {
                    
                    } else {
                        this->oErrorLogger->fnErrorF("Error in configuration file '%s' at line %d", 0, sFilePath.c_str(), iLineNumber);
                        this->bIsLoaded = false;
                        break;
                    }
                }
            }
        }
        
        if (!bStringFlag) {
            if (cChar=='\n') {
                sVarValue = "";
                sVarName = "";
                iLineNumber++;
            }
        }
        
        oFileBuf.snextc();
    } 
    
    oFileBuf.close();
    this->bIsLoaded = true;
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

bool Configuration::fnIsLoaded() 
{
    return this->bIsLoaded;
}
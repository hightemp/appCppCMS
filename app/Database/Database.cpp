
#include "Database.hpp"

Database(Logger *oErrorLogger, Configuration *oConfiguration)
{
    this->oErrorLogger = oErrorLogger;
    this->poDriver = get_driver_instance();
    this->fnCreateConnection(
        "Main", 
        oConfiguration->fnGetString("sDatabaseHost"), 
        oConfiguration->fnGetString("sDatabaseUser"), 
        oConfiguration->fnGetString("sDatabasePassword"), 
        oConfiguration->fnGetString("sDatabaseDatabase")
    );
}

Database::~Database()
{
    
}

void Database::fnCreateConnection(
    std::string sName, 
    std::string sURL, 
    std::string sUser,
    std::string sPassword,
    std::string sDatabase
)
{
    this->oConnections[sName] = {};
    this->oConnections[sName].sName = sName;
    this->oConnections[sName].sURL = sURL;
    this->oConnections[sName].sUser = sUser;
    this->oConnections[sName].sPassword = sPassword;
    this->oConnections[sName].sDatabase = sDatabase;
    this->oConnections[sName].poConnection = PConnection(this->poDriver->connect(sURL, sUser, sPassword));
    
	this->oConnections[sName].poConnection->setSchema(sDatabase);
	
	this->sCurrentConnetionName = sName;
}

std::string Database::fnFormatQuery(std::string sQuery, ...)
{
    va_list pArguments;
    va_start(pArguments, sQuery);
    
    bool bVarFlag = false;
    std::stringstream ssResultQuery;
    
    try {
        std::for_each(sQuery.begin(), sQuery.end(), [&](char cChar) {
            if (!bVarFlag) {
                if (cChar==':') {
                    bVarFlag = true;
                } else {
                    ssResultQuery << cChar;
                }
            } else {
                switch(cChar) {
                    case 'i':
                            ssResultQuery << va_arg(pArguments, int);
                        break;
                    case 'f':
                            ssResultQuery << va_arg(pArguments, float);
                        break;
                    case 'd':
                            ssResultQuery << va_arg(pArguments, double);
                        break;
                    case 's':
                            ssResultQuery << "'" << va_arg(pArguments, std::string) << "'";
                        break;
                    case 'c':
                            ssResultQuery << "'" << va_arg(pArguments, char *) << "'";
                        break;
                    default:
                            ssResultQuery << ':';
                            ssResultQuery << cChar;
                        break;
                }
                
                bVarFlag = false;
            }
        });
    } catch (std::exception& oException) {
        this->oErrorLogger->fnErrorF("Exception catched: %s", 0, oException.what());
    }
    
    va_end(pArguments); 
    
    return ssResultQuery.str();
}

void Database::fnQuery(std::string sQuery)
{
    auto &poConnection = this->oConnections[this->sCurrentConnetionName].poConnection;
    
    PStatement poStatement(poConnection->createStatement());
    
    poStatement->execute(sQuery);
}

PResultSet Database::fnGetRows(std::string sQuery)
{
    auto &poConnection = this->oConnections[this->sCurrentConnetionName].poConnection;
    
    PStatement poStatement(poConnection->createStatement());
    return PResultSet(poStatement->executeQuery(sQuery));
}

std::string Database::fnGetField(std::string sQuery)
{
    PResultSet poResult = this->fnGetRows(sQuery);

    if (poResult->next()) {
        return poResult->getString(1);
    }
    
    return "";
}

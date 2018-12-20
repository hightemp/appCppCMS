
#include "HTTPProxy.hpp"

std::vector<HTTPProxy *> ProxyManager::oProxy;

HTTPProxy::HTTPProxy(const char *sHost, int iPort)
{
    this->iPort = iPort;
    
    this->sHost = std::string(sHost);
}

HTTPProxy::~HTTPProxy()
{

}

void ProxyManager::fnParseEnv()
{
    const char *aEnvNames[] = {
        "http_proxy"
    };
    
    for (int iIndex=0; iIndex<(sizeof(aEnvNames) / sizeof(char *)); iIndex++) {
        ProxyManager::fnParseEnvVarAndAddProxy(aEnvNames[iIndex]);
    }
}

void ProxyManager::fnParseEnvVarAndAddProxy(const char *sEnvVarName)
{
    char* sEnvVar = std::getenv(sEnvVarName);
    
    if (!sEnvVar) {
        return;
    }
    
    std::string sProxy = std::string(sEnvVar);
    
    printf("%s=%s\n", sEnvVarName, sProxy.c_str());
    
    int iSeparatorPos = sProxy.find(":");
    
    std::string sHostname;
    int iPort;
    
    if (iSeparatorPos!=std::string::npos) {
        sHostname = sProxy.substr(iSeparatorPos, sProxy.length()-iSeparatorPos);
        std::string sPort = sProxy.substr(0, iSeparatorPos-1);
        iPort = atoi(sPort.c_str());
    } else {
        sHostname = sProxy;
        iPort = 80;
    }
    
    ProxyManager::oProxy.push_back(new HTTPProxy(sHostname.c_str(), iPort));
}



#include <cstdlib>
#include <string>
#include <stdio.h>
#include <memory>
#include <vector>


class HTTPProxy
{
    public:
        int iPort;
        std::string sHost;
    
        HTTPProxy(const char *sHost, int iPort);
        ~HTTPProxy();
};

class ProxyManager
{
    public:
        static std::vector<HTTPProxy *> oProxy;
    
        static void fnParseEnv();
        static void fnParseEnvVarAndAddProxy(const char *sEnvVarName);
};
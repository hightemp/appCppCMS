
#include "main.hpp"

int main(int argc, char **argv, char** env)
{
    try {
        oApplication.fnRun(argc, argv, env);
    } catch(std::exception& oException) {
        oApplication.oErrorLogger.fnError(oException.what(), 0);
    }
    
    return 0;
}
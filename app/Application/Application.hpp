
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Logger.hpp"
#include "View.hpp"
#include "Response.hpp"
#include "Database.hpp"
#include "Configuration.hpp"
#include "FileSystem.hpp"
#include "DateTime.hpp"

#include "Types.hpp"
#include "BaseController.hpp"

class Application
{
    TStringBaseControllerUnorderedMap oControllers;
    
    public:
        Logger oErrorLogger("errors.log", 0);
        Configuration oConfiguration;
        Logger oLogger;
        View oView;
        Response oResponse;
        Database oDatabase;
        
        Application(): oConfiguration(), oLogger(oConfiguration), oDatabase(&oErrorLogger, oConfiguration) {}
        ~Application();
        
        void fnRun();
        
        void fnAddController(std::string sControllerName, BaseController *pPointer);
        void fnCallControllerMethod(std::string sControllerName, std::string sControllerMethodName);
};

#endif
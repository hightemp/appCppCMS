
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "lib/segvcatch/lib/segvcatch.h"
#include <stdexcept>

#include "Logger.hpp"
#include "View.hpp"
#include "Response.hpp"
#include "Database.hpp"
#include "Configuration.hpp"
#include "FileSystem.hpp"
#include "DateTime.hpp"

#include "Types.hpp"
#include "BaseController.hpp"

void handle_segv();
void handle_fpe();

class Application
{
    TStringBaseControllerUnorderedMap oControllers;
    
    public:
        Logger oErrorLogger;
        Configuration oConfiguration;
        Logger oLogger;
        View oView;
        Response oResponse;
        Database oDatabase;
        
        Application(): 
            oErrorLogger("errors.log", 0),
            oConfiguration(&oErrorLogger), 
            oLogger(&oConfiguration),
            oDatabase(&oErrorLogger, &oConfiguration) 
        {
            segvcatch::init_segv(&handle_segv);
            segvcatch::init_fpe(&handle_fpe);
        }
        ~Application();
        
        void fnRun();
        
        void fnAddController(std::string sControllerName, BaseController *pPointer);
        void fnCallControllerMethod(std::string sControllerName, std::string sControllerMethodName);
};

extern Application oApplication;

#endif
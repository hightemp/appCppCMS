
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "lib/segvcatch/lib/segvcatch.h"
#include <stdexcept>

#include "Types.hpp"
#include "Logger.hpp"
#include "View.hpp"
#include "Response.hpp"
#include "Configuration.hpp"
#include "Database.hpp"
#include "FileSystem.hpp"
#include "DateTime.hpp"
#include "Request.hpp"

void handle_segv();
void handle_fpe();

class BaseController;
class Logger;
class Configuration;
class View;
class Response;
class Database;
class Request;

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
        Request oRequest;
        
        TStringStringUnorderedMap oEnvironmentVars;
    
        const std::string saEnvironmentVarsNames[24] = {
           "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",   
           "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",             
           "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",         
           "HTTP_HOST", "HTTP_USER_AGENT", "PATH",            
           "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",      
           "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
           "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",      
           "SERVER_NAME", "SERVER_PORT", "SERVER_PROTOCOL",     
           "SERVER_SIGNATURE", "SERVER_SOFTWARE"
        };
   
        Application(): 
            oErrorLogger("errors.log", 0),
            oConfiguration(&oErrorLogger), 
            oLogger(&oConfiguration),
            oDatabase(&oErrorLogger, &oConfiguration),
            oRequest(this)
        {
            segvcatch::init_segv(&handle_segv);
            segvcatch::init_fpe(&handle_fpe);
        }
        ~Application();
        
        void fnRun(int &iArgCount, char **&cppArgs, char **&cppEnvironment);
        
        void fnAddController(std::string sControllerName, BaseController *pPointer);
        void fnCallControllerMethod(std::string sControllerName, std::string sControllerMethodName);
};

extern Application oApplication;

#endif
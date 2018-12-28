
#include "Application.hpp"

void handle_segv()
{
    oApplication.oErrorLogger.fnError("Segmentation fault", 0);
    throw std::runtime_error("SEGV");
}

void handle_fpe()
{
    oApplication.oErrorLogger.fnError("Floating point exception", 0);
    throw std::runtime_error("FPE");
}

Application oApplication;

Application::~Application()
{
    
}

void Application::fnRun()
{
    this->fnCallControllerMethod("InstallationController", "fnTest");
    
    this->oResponse.fnSetContent(this->oView);
    this->oResponse.fnFlush();
}

void Application::fnAddController(std::string sControllerName, BaseController *pPointer)
{
    this->oControllers[sControllerName] = pPointer;
}

void Application::fnCallControllerMethod(std::string sControllerName, std::string sControllerMethodName)
{
    this->oControllers[sControllerName]->fnCallMethod(sControllerMethodName);
}
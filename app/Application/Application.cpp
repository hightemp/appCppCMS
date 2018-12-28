
#include "Application.hpp"

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
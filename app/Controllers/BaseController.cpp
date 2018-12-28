
#include "BaseController.hpp"

void BaseController::fnAddControllerFunction(
    std::string sControllerFunctionName,
    TControllerMethod pPointer
)
{
    this->oControllersMethods[sControllerFunctionName] = pPointer;
}

void BaseController::fnCallMethod(std::string sControllerFunctionName)
{
    (this->*this->oControllersMethods[sControllerFunctionName])();
}

bool BaseController::fnMethodExists(std::string sControllerFunctionName)
{
    return this->oControllersMethods.find(sControllerFunctionName)!=this->oControllersMethods.end();
}
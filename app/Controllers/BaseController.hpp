
#ifndef BASE_CONTROLLER_HPP
#define BASE_CONTROLLER_HPP

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Types.hpp"

class BaseController
{
    TStringTControllerMethodUnorderedMap oControllersMethods;

    public:
        BaseController() {}
        virtual ~BaseController() {}
        
        void fnAddControllerFunction(
            std::string sControllerFunctionName,
            TControllerMethod pPointer
        );
        void fnCallMethod(std::string sControllerFunctionName);
        bool fnMethodExists(std::string sControllerFunctionName);
};

#endif
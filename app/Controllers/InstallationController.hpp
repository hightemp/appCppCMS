
#ifndef INSTALLATION_CONTROLLER_HPP
#define INSTALLATION_CONTROLLER_HPP

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Types.hpp"
#include "BaseController.hpp"

class Application;

//extern Application oApplication;

class InstallationController : BaseController
{
    public:
        InstallationController(Application *oApplication);
        
        void fnTest();
};

extern InstallationController oInstallationController;

#endif
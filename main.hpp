
#ifndef MAIN_HPP
#define MAIN_HPP

#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <malloc.h>

#include "Logger.hpp"
#include "View.hpp"
#include "Response.hpp"
#include "Configuration.hpp"
#include "Database.hpp"
#include "FileSystem.hpp"
#include "DateTime.hpp"
#include "Request.hpp"

#include "BaseController.hpp"

#include "Application.hpp"

extern Application oApplication;

#include "InstallationController.hpp"

#endif

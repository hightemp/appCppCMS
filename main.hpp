
#ifndef MAIN_HPP
#define MAIN_HPP

#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cgicc/Cgicc.h>
#include "lib/segvcatch/lib/segvcatch.h"
#include <stdexcept>
#include <malloc.h>

#include "Logger.hpp"
#include "HTTPProxy.hpp"
#include "View.hpp"
#include "Response.hpp"
#include "Database.hpp"
#include "Configuration.hpp"

class Logger;
class Configuration;

extern Logger oErrorLogger;
extern Configuration oConfiguration;
extern Logger oLogger;
extern View oView;
extern Response oResponse;
extern Database oDatabase;

#endif

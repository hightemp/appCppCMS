
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cgicc/Cgicc.h>
#include "lib/segvcatch/lib/segvcatch.h"
#include <stdexcept>
#include <malloc.h>

#include "HTTPProxy.hpp"
#include "View.hpp"
#include "Response.hpp"
#include "Database.hpp"
#include "Configuration.hpp"

extern Configuration oConfiguration;
extern View oView;
extern Response oResponse;
extern Database oDatabase;

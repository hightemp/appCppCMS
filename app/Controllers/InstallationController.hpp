
#ifndef INSTALLATION_CONTROLLER_HPP
#define INSTALLATION_CONTROLLER_HPP

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Types.hpp"
#include "Database.hpp"
#include "BaseController.hpp"
#include "Application.hpp"

extern Application oApplication;

class InstallationController : BaseController
{
    public:
        InstallationController()
        {
            std::cout << "InstallationController" << std::endl;
            oApplication.fnAddController("InstallationController", this);
            this->fnAddControllerFunction("fnTest", (TControllerMethod) &InstallationController::fnTest);
        }
        
        void fnTest()
        {
            std::cout << "TEST2" << std::endl;
            oApplication.oView.fnAddScriptSrc("test.js");
            oApplication.oView.fnHTML5Open();
            
            oApplication.oDatabase.fnQuery("DROP TABLE IF EXISTS test");
            oApplication.oDatabase.fnQuery("CREATE TABLE test(id INT, label CHAR(1))");
            oApplication.oDatabase.fnQuery("INSERT INTO test(id, label) VALUES (1, 'a')");
            
            PResultSet poResult = oApplication.oDatabase.fnGetRowsF("SELECT id, label FROM test WHERE id>:i ORDER BY id ASC", 0);
            oApplication.oView << '"' << oApplication.oDatabase.fnGetFieldF("SELECT id, label FROM test WHERE id>:i ORDER BY id ASC", 0) << '"' << "<br>";
            while (poResult->next()) {
                // You can use either numeric offsets...
                oApplication.oView << "id = " << poResult->getInt(1) << "<br>"; // getInt(1) returns the first column
                // ... or column names for accessing results.
                // The latter is recommended.
                oApplication.oView << ", label = '" << poResult->getString("label") << "'" << "<br>";
            }
            
            oApplication.oView.fnHTML5Close();
        }
};

extern InstallationController oInstallationController;

#endif
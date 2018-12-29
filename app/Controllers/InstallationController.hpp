
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
        InstallationController(Application *oApplication): BaseController(oApplication)
        {
            std::cout << "InstallationController" << std::endl;
            this->oApplication->fnAddController("InstallationController", this);
            this->fnAddControllerFunction("fnTest", (TControllerMethod) &InstallationController::fnTest);
        }
        
        void fnTest()
        {
            std::cout << "TEST2" << std::endl;
            this->oApplication->oView.fnAddScriptSrc("test.js");
            this->oApplication->oView.fnHTML5Open();
            
            this->oApplication->oDatabase.fnQuery("DROP TABLE IF EXISTS test");
            this->oApplication->oDatabase.fnQuery("CREATE TABLE test(id INT, label CHAR(1))");
            this->oApplication->oDatabase.fnQuery("INSERT INTO test(id, label) VALUES (1, 'a')");
            
            PResultSet poResult = this->oApplication->oDatabase.fnGetRowsF("SELECT id, label FROM test WHERE id>:i ORDER BY id ASC", 0);
            this->oApplication->oView << '"' << this->oApplication->oDatabase.fnGetFieldF("SELECT id, label FROM test WHERE id>:i ORDER BY id ASC", 0) << '"' << "<br>";
            while (poResult->next()) {
                // You can use either numeric offsets...
                this->oApplication->oView << "id = " << poResult->getInt(1) << "<br>"; // getInt(1) returns the first column
                // ... or column names for accessing results.
                // The latter is recommended.
                this->oApplication->oView << ", label = '" << poResult->getString("label") << "'" << "<br>";
            }
            
            this->oApplication->oView.fnHTML5Close();
        }
        
};

extern InstallationController oInstallationController;

#endif

#include "main.hpp"

using namespace std;
using namespace cgicc;

View oView;
Response oResponse;
Database oDatabase;

void handle_segv()
{
    throw std::runtime_error("SEGV");
}

void handle_fpe()
{
    throw std::runtime_error("FPE");
}

int main(int argc, char **argv, char** env)
{
    segvcatch::init_segv(&handle_segv);
    segvcatch::init_fpe(&handle_fpe);
    
    oView.fnWriteToBuffer("1\n");
    oView.fnStartBuffer("test");
        oView.fnWriteToBuffer("2\n");
    oView.fnEndBuffer();
    oView.fnWriteToBuffer("3\n");
    
    oResponse.fnSetContent(oView);
    oResponse.fnFlush();
    
    oDatabase.fnQuery("DROP TABLE IF EXISTS test");
    oDatabase.fnQuery("CREATE TABLE test(id INT, label CHAR(1))");
    oDatabase.fnQuery("INSERT INTO test(id, label) VALUES (1, 'a')");
    
    PResultSet poResult = oDatabase.fnGetRowsF("SELECT id, label FROM test WHERE id>:i ORDER BY id ASC", 0);
    cout << '"' << oDatabase.fnGetFieldF("SELECT id, label FROM test WHERE id>:i ORDER BY id ASC", 0) << '"' << endl;
    while (poResult->next()) {
        // You can use either numeric offsets...
        cout << "id = " << poResult->getInt(1); // getInt(1) returns the first column
        // ... or column names for accessing results.
        // The latter is recommended.
        cout << ", label = '" << poResult->getString("label") << "'" << endl;
    }

    /*
    void* handle = dlopen("./addons/test/addon.so", RTLD_LAZY);
    
    if (!handle)
    {
        printf("The error is %s", dlerror());
    }

    void (*test_output)(...);

    test_output = (void (*)(...))dlsym(handle, "test_output");
    
    Cgicc formData;
    
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>Using GET and POST Methods</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    
    ProxyManager::fnParseEnv();
    
    int *p = (int *)malloc(sizeof(int));

    cout << sizeof(int) << endl;
    cout << malloc_usable_size(p) << endl;
    cout << malloc_usable_size(handle) << endl;

    try {
        *(int*) 0 = 0;
        test_output(1, "test arg");
    } catch (std::exception& oException) {
        std::cerr << "Exception catched : " << oException.what() << std::endl;
    }

    form_iterator fi = formData.getElement("first_name");
    if(fi != (*formData).end()) {
        cout << "First name: " << **fi << endl;
    }else{
        cout << "No text entered for first name" << endl;
    }
    cout << "<br/>\n";
    fi = formData.getElement("last_name");
    if(fi != (*formData).end()) {
        cout << "Last name: " << **fi << endl;
    }else{
        cout << "No text entered for last name" << endl;
    }
    cout << "<br/>\n";

    cout << "</body>\n";
    cout << "</html>\n";
    */
    return 0;
}
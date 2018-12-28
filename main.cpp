
#include "main.hpp"

using namespace cgicc;

void handle_segv()
{
    oErrorLogger.fnError("Segmentation fault", 0);
    throw std::runtime_error("SEGV");
}

void handle_fpe()
{
    oErrorLogger.fnError("Floating point exception", 0);
    throw std::runtime_error("FPE");
}

struct Initializer
{
    Initializer()
    {
        segvcatch::init_segv(&handle_segv);
        segvcatch::init_fpe(&handle_fpe);
    }
};

Initializer oInitializer;
Application oApplication;

int main(int argc, char **argv, char** env)
{
    oApplication.fnRun();

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
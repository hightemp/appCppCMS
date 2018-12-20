//#include <iostream>
#include <stdio.h>
#include <cstdarg>

//using namespace std;

extern "C" void test_output(int argc, ...)
{
  va_list args;
  
  va_start(args, argc);
  for(int i = 0; i < argc; i++)
    printf("%s", va_arg(args, char*));
  va_end(args);
  
  void (*npf)() = 0;
  
  npf();
  //printf("test");
}
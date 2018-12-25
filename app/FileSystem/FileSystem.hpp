
#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <libgen.h>

class FileSystem
{
    public:
        static std::string fnGetCurrentDir();
        static std::string fnGetExecutablePath();
        static std::string fnGetExecutableDirPath();
};

#endif
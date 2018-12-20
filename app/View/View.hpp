
#ifndef VIEW_HPP
#define VIEW_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

class View
{
    std::unordered_map<std::string, std::string> oBuffers;
    std::vector<std::string> oBufferStack;
    
    public:
        View();
        ~View();

        std::string fnGetContent();
        void fnFlush();
        void fnStartBuffer(std::string sName);
        void fnEndBuffer();
        std::string fnGetBufferContents();
        void fnCleanBuffer();
        void fnFlushBuffer();
        void fnWriteToBuffer(std::string sString);
        void fnSetBufferContents(std::string sString);
        std::string fnGetCurrentBufferName();

};

#endif
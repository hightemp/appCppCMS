
#ifndef VIEW_HPP
#define VIEW_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "Types.hpp"

class View
{
    TStringStringUnorderedMap oBuffers;
    TStringVector oBufferStack;
    TStringVector oOpenedTags;
    
    TStringStringUnorderedMapVector oMetaTags={{{"charset", "utf-8"}}};
    std::string sEncoding = "utf-8";
    
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

        bool fnHasOpenedTags();
        void fnTag(std::string sTagName, TStringStringUnorderedMap oAttributes={});
        void fnSingleTag(std::string sTagName, TStringStringUnorderedMap oAttributes={});
        void fnCloseTag();
        
        void fnHTML5Open();
        void fnHTML5Close();
};

#endif

#ifndef VIEW_HPP
#define VIEW_HPP

#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

#include "Types.hpp"

class View
{
    TStringStringUnorderedMap oBuffers;
    TStringVector oBufferStack;
    TStringVector oOpenedTags;
    
    TStringStringUnorderedMapVector oMetaTags={{{"charset", "utf-8"}}};
    TStringStringUnorderedMapVector oLinkTags;
    TStringStringUnorderedMapVector oScriptTags;
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
        std::string fnGetSingleTag(std::string sTagName, TStringStringUnorderedMap oAttributes={});
        void fnCloseTag();
        
        void fnHTML5Open();
        void fnHTML5Close();

        void fnAddLink(TStringStringUnorderedMap oAttributes);
        void fnAddLinkStyle(std::string sPath);
        void fnAddMeta(TStringStringUnorderedMap oAttributes);
        void fnAddScript(TStringStringUnorderedMap oAttributes);
        void fnAddScriptSrc(std::string sPath);
        void fnScriptTags();
        std::string fnGetScriptTags();
};

inline View& operator<<(View& oView, std::string sValue)
{
    oView.fnWriteToBuffer(sValue);
    return oView;
}

inline View& operator<<(View& oView, int iValue)
{
    oView.fnWriteToBuffer(std::to_string(iValue));
    return oView;
}

#endif
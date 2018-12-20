
#include "View.hpp"

View::View()
{
    this->oBuffers["Main"] = "";
    
    this->oBufferStack.push_back("Main");
}

View::~View()
{
    
}

std::string View::fnGetContent()
{
    return this->oBuffers["Main"];
}

void View::fnFlush()
{
    std::cout << this->fnGetContent();
}

void View::fnStartBuffer(std::string sName)
{
    for (std::string &sBufferName : this->oBufferStack) {
        if (sBufferName==sName) {
            std::runtime_error("Buffer already in usage");
        }
    }
    
    if (this->oBuffers.find(sName)==this->oBuffers.end()) {
        this->oBuffers[sName] = "";
    }
    
    this->oBufferStack.push_back(sName);
}

void View::fnEndBuffer()
{
    if (this->oBufferStack.size()>1) {
        this->oBufferStack.pop_back();
    }
}

std::string View::fnGetBufferContents()
{
    return this->oBuffers[this->fnGetCurrentBufferName()];
}

void View::fnCleanBuffer()
{
    this->oBuffers[this->fnGetCurrentBufferName()] = "";
}

void View::fnFlushBuffer()
{
    std::cout << this->oBuffers[this->fnGetCurrentBufferName()];
}

void View::fnWriteToBuffer(std::string sString)
{
    this->oBuffers[this->fnGetCurrentBufferName()] += sString;
}

void View::fnSetBufferContents(std::string sString)
{
    this->oBuffers[this->fnGetCurrentBufferName()] = sString;
}

std::string View::fnGetCurrentBufferName()
{
    return this->oBufferStack.back();
}

bool View::fnHasOpenedTags()
{
    return this->oOpenedTags.size()>0;
}

void View::fnTag(std::string sTagName, TStringStringUnorderedMap oAttributes)
{
    this->oOpenedTags.push_back(sTagName);
    this->fnSingleTag(sTagName, oAttributes);
}

void View::fnSingleTag(std::string sTagName, TStringStringUnorderedMap oAttributes)
{
    bool bDoctype = sTagName.find("doctype")!=std::string::npos;
    
    auto &rOutput = this->oBuffers[this->fnGetCurrentBufferName()];
    
    rOutput += "<"; 
    if (bDoctype) 
        rOutput += "!";
    rOutput += sTagName;
    
    for (TStringStringPair oPair : oAttributes) {
        rOutput += " " + oPair.first + "='" + oPair.second + "'";
    }
    
    if (bDoctype) 
        rOutput += " html";
    rOutput += ">";
}

void View::fnCloseTag()
{
    auto &rOutput = this->oBuffers[this->fnGetCurrentBufferName()];
    
    rOutput += "</" + this->oOpenedTags.back() + ">";
    
    this->oOpenedTags.pop_back();
}

void View::fnHTML5Open()
{
    this->fnSingleTag("doctype");
    
    this->fnTag("html");
    
        this->fnTag("head");
            for (auto &oTagAttributes : oMetaTags) {
                this->fnTag("meta", oTagAttributes);
            }
            //this->fnTag("meta", {{"charset", "utf-8"}});
        this->fnCloseTag();
        
        this->fnTag("body");
        
}

void View::fnHTML5Close()
{
        this->fnCloseTag();
    this->fnCloseTag();
}

/*
<!doctype html>

<html lang="en">
<head>
  <meta charset="utf-8">

  <title>The HTML5 Herald</title>
  <meta name="description" content="The HTML5 Herald">
  <meta name="author" content="SitePoint">

  <link rel="stylesheet" href="css/styles.css?v=1.0">

</head>

<body>
  <script src="js/scripts.js"></script>
</body>
</html>
*/
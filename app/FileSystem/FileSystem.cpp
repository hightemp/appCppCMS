
#include "FileSystem.hpp"


std::string FileSystem::fnGetCurrentDir()
{
    char caCurrentDir[FILENAME_MAX];
    
    getcwd(caCurrentDir, FILENAME_MAX);
    
    std::string sCurrentDir(caCurrentDir);
    
    return sCurrentDir;
}

std::string FileSystem::fnGetExecutablePath()
{
    static std::string sPath;
    
    if (sPath.empty()) {
        char caPath[FILENAME_MAX];
        
        readlink("/proc/self/exe", caPath, FILENAME_MAX);
        
        sPath = caPath;
    }
    
    return sPath;
}

std::string FileSystem::fnGetExecutableDirPath()
{
    std::string sPath = FileSystem::fnGetExecutablePath();
    
    char pPath[FILENAME_MAX];
    strcpy(pPath, sPath.c_str()); 
    
    char *pDirPath = dirname(pPath);
    
    sPath = pDirPath;
    
    return sPath;
}

std::string FileSystem::fnGetFullPath(std::string sFileName)
{
    std::string sFilePath;
    
    if (sFileName.length()<1) {
        return sFilePath;
    }
    
    if (sFileName[0]=='/') {
        sFilePath = sFileName;
    } else {
        std::string sCurrentDir = FileSystem::fnGetExecutableDirPath();
        sFilePath = sCurrentDir + "/" + sFileName;
    }
    
    return sFilePath;
}
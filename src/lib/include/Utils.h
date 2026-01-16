#ifndef _UTILS_H__
#define _UTILS_H__

#include <string>
#include "FolderManager.h"

class Utils {
public:
    static std::string StringReplace(std::string base, std::string tag, std::string replacement);
    static std::string GetTemplate(FolderManager::FILE_CONTENT templateType, std::string base);
    static std::string Parse(std::string path);
    static std::string ToUpper(std::string const& pStr);
};

#endif

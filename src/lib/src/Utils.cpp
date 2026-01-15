#include "Utils.h"
#include "FolderManager.h"
#include <fstream>
std::string Utils::StringReplace(std::string base, std::string tag, std::string replacement)
{
    if(base.find(tag) == std::string::npos)
        return "";

    base.replace(base.find(tag), base.length(), replacement);
    
    return base;
}

std::string Utils::Parse(std::string path)
{
    std::fstream s(path, std::ios::in);
    if(s.is_open() == false)
        return "";

    std::string out;
    std::string line;
    while(getline(s, line))
    {
        out += line;
    }
    return line;
}

std::string Utils::GetTemplate(FolderManager::FILE_CONTENT templateType)
{
    switch(templateType)
    {
        case FolderManager::FILE_CONTENT::CMAKE_APP:
            return Utils::Parse("../res/templates/CMakeApp_template.txt");
        case FolderManager::FILE_CONTENT::CMAKE_GEN:
            return Utils::Parse("../res/templates/CMakeGen_template.txt");

    }
}

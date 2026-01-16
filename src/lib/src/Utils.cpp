#include "Utils.h"
#include "FolderManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::string Utils::StringReplace(std::string base, std::string tag, std::string replacement)
{
    if(base.find(tag) == std::string::npos)
        return base;
    base.replace(base.find(tag), tag.length(), replacement);
    
    return base;
}

std::string Utils::Parse(std::string path)
{
    std::fstream s(path, std::ios::in);

    if(s.is_open() == false)
    {
        std::cout<<"failed"<<std::endl;
        return "";
    }

    std::ostringstream sstr;
    sstr << s.rdbuf();

    s.close();
    return sstr.str();
}

std::string Utils::GetTemplate(FolderManager::FILE_CONTENT templateType, std::string base)
{
    switch(templateType)
    {
        case FolderManager::FILE_CONTENT::CMAKE_APP:
            return Utils::Parse(base + "/../res/templates/CMakeApp_template.txt");
            break;
        case FolderManager::FILE_CONTENT::CMAKE_GEN:
            return Utils::Parse(base + "/../res/templates/CMakeGen_template.txt");
            break;
        case FolderManager::FILE_CONTENT::CMAKE_LIB:
            return Utils::Parse(base + "/../res/templates/CMakeLib_template.txt");
            break;
        case FolderManager::FILE_CONTENT::INCLUDE:
            return Utils::Parse(base + "/../res/templates/include_template.h");
            break;
        case FolderManager::FILE_CONTENT::MAIN:
            return Utils::Parse(base + "/../res/templates/main_template.cpp");
            break;
        case FolderManager::FILE_CONTENT::SRC:
            return Utils::Parse(base + "/../res/templates/main_template.cpp");
            break;
        default:
            return "";
    }
}

std::string Utils::ToUpper(std::string const& str)
{
    std::string out;
    for(int i = 0; i< str.size(); ++i)
    {
        out += toupper(str[i]);
    }

    return out;
}

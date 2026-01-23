#include "Settings.h"
#include <string.h>

Settings::Settings(int argc, char** argv):
    m_argc(argc),
    m_argv(argv)
{

}

std::map<char*, std::vector<char*>> Settings::Parse()
{
    std::map<char*, std::vector<char*>> result; 
    int index = 2;
    for(int i = 0; i<m_argc; ++i)
    {
        if(strcmp(m_argv[i], "-r") == 0 || strcmp(m_argv[i], "--root") == 0)
        {
            result[m_argv[i + 1]] = _GetDependencies(m_argc, m_argv, index);
        }

        if(strcmp(m_argv[i], "-a") == 0 || strcmp(m_argv[i], "--app") == 0)
        {
            result[m_argv[i + 1]] = _GetDependencies(m_argc, m_argv, index);
        }

        if(strcmp(m_argv[i], "-l") == 0 || strcmp(m_argv[i], "--lib") == 0)
        {
            result[m_argv[i + 1]] = _GetDependencies(m_argc, m_argv, index);
        }
    }

    return result;
}

std::vector<char*> Settings::_GetDependencies(int argc, char** argv, int index)
{
    std::vector<char*> dependencies;
    int argument = 2;
    while(argv[index + argument][0] != '-' || index + argument >= argc)
    {
        dependencies.push_back(argv[index + argument]);
        argument++;
    }

    return dependencies;
}

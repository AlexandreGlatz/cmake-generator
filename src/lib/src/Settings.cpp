#include "Settings.h"
#include <string.h>
#include <iostream>
Settings::Settings(int argc, char** argv):
    m_argc(argc),
    m_argv(argv),
    m_projectDependencies()
{

}

Settings::~Settings()
{

}

void Settings::Parse()
{
    m_executable = m_argv[0];
    if(m_argc == 1)
    {
        m_projectDependencies["app"] = {"lib"}; 
        m_projectDependencies["lib"] = {}; 
        m_rootName = "project";
        return;
    }

    for(int i = 1; i<m_argc; ++i)
    {
        std::cout<<i<<std::endl;
        if(strcmp(m_argv[i], "-r") == 0 || strcmp(m_argv[i], "--root") == 0)
        {
            m_rootName = m_argv[i+1];
            i++;
        }

        else if(strcmp(m_argv[i], "-a") == 0 || strcmp(m_argv[i], "--app") == 0)
        {
            std::vector<const char*> dependencies = _GetDependencies(m_argc, m_argv, i);
            m_projectDependencies[m_argv[i + 1]] = dependencies;
            i += dependencies.size() + 1;
        }
        else if(strcmp(m_argv[i], "-l") == 0 || strcmp(m_argv[i], "--lib") == 0)
        {
            std::vector<const char*> dependencies = _GetDependencies(m_argc, m_argv, i);
            m_projectDependencies[m_argv[i + 1]] = dependencies;
            i += dependencies.size() + 1;
        }
        else
        {
            std::cout<<"command : "<<m_argv[i]<<" does not exist, use -h for help"<<std::endl;
        }
    }
}

std::vector<const char*> Settings::_GetDependencies(int argc, char** argv, int index)
{
    
    std::vector<const char*> dependencies;
    int argument = 2;
    if(index + argument >= argc)
        return dependencies;

    while(argv[index + argument][0] != '-' && index + argument < argc)
    {
        std::cout<<argv[index + argument]<<std::endl;
        dependencies.push_back(argv[index + argument]);
        argument++;
    }

    return dependencies;
}

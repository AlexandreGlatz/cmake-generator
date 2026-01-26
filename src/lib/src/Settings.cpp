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
            m_appName = m_argv[i + 1];
            _CreateDependencies(i);
        }
        else if(strcmp(m_argv[i], "-l") == 0 || strcmp(m_argv[i], "--lib") == 0)
        {
            _CreateDependencies(i);
        }
        else
        {
            std::cout<<"command : "<<m_argv[i]<<" does not exist, use -h for help"<<std::endl;
        }
    }
}

void Settings::_CreateDependencies(int& index)
{
    int argument = 2;

    m_projectDependencies[m_argv[index + 1]] = {};
    if(index + argument >= m_argc)
    {
        index += 1;
        return;
    }

    while(m_argv[index + argument][0] != '-' && index + argument < m_argc)
    {
        std::cout<<m_argv[index + 1]<<std::endl;
        m_projectDependencies[m_argv[index + 1]].push_back(m_argv[index + argument]);
        argument++;
    }

    index += argument - 1;
}

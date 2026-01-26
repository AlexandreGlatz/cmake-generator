#include "FolderManager.h"
#include "Settings.h"
#include <filesystem>
#include <iostream>

int main(int argc, char* argv[])
{
    Settings settings(argc, argv);
    settings.Parse();

    std::cout<<"executable : "<<settings.GetExecutable()<<std::endl;
    std::cout<<"rootName : "<<settings.GetRootName()<<std::endl;
    std::cout<<"appName : "<<settings.GetAppName()<<std::endl;
    std::map<const char*, std::vector<const char*>> projDepen = settings.GetProjectDependencies();
    for(auto const& [key, value] : projDepen)
    {
        std::cout<<key<<" : "<<std::endl;
        for(auto const& val : value)
            std::cout<<val<<std::endl;
    } 

    FolderManager* pFolderManager = FolderManager::GetInstance();
    pFolderManager->GenerateContents(settings);
    pFolderManager->CreateArchitecture();
}

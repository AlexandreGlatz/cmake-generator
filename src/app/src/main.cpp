#include "FolderManager.h"
#include "Settings.h"
#include <filesystem>
#include <iostream>

int main(int argc, char* argv[])
{
//    FolderManager* pFolderManager = FolderManager::GetInstance();
    //pFolderManager->GenerateContents(argv, argc);
    //pFolderManager->CreateArchitecture();
    Settings settings(argc, argv);
    settings.Parse();

    std::cout<<"executable : "<<settings.GetExecutable()<<std::endl;
    std::cout<<"rootName : "<<settings.GetRootName()<<std::endl;
    std::map<const char*, std::vector<const char*>> projDepen = settings.GetProjectDependencies();
    for(auto const& [key, value] : projDepen)
    {
        std::cout<<key<<" : "<<std::endl;
        for(auto const& val : value)
            std::cout<<val<<std::endl;
    }
}

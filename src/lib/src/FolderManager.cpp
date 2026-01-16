#include "FolderManager.h"
#include "Folder.h"
#include "File.h"
#include "Utils.h"
#include <iostream>

FolderManager* FolderManager::m_instance;
FolderManager::FolderManager()
{}

FolderManager* FolderManager::GetInstance()
{
    if(m_instance==nullptr)
    {
        m_instance = new FolderManager();
    }
    return m_instance;
}

void FolderManager::CreateArchitecture()
{
    File cmakeGen("CMakeLists.txt", 
            m_projects[0]->fileContents[FILE_CONTENT::CMAKE_GEN]->content, 
            m_projects[0]->fileContents[FILE_CONTENT::CMAKE_GEN]->size);
    Folder build("build/");
    Folder resources("res/");
    
    { //app
        Folder app("app/");
        app.CreateSubFile("CMakeLists.txt", 
                m_projects[1]->fileContents[FILE_CONTENT::CMAKE_APP]->content,
                m_projects[1]->fileContents[FILE_CONTENT::CMAKE_APP]->size);

        Folder* appSrc = app.CreateSubfolder("src/");
        appSrc->CreateSubFile("main.cpp", 
                m_projects[1]->fileContents[FILE_CONTENT::MAIN]->content, 
                m_projects[1]->fileContents[FILE_CONTENT::MAIN]->size);
    }

    for(int i = 2; i<m_projects.size(); ++i)
    { //lib
        Folder lib(m_projects[i]->name + "/");
        lib.CreateSubFile("CMakeLists.txt", 
                m_projects[i]->fileContents[FILE_CONTENT::CMAKE_LIB]->content,
                m_projects[i]->fileContents[FILE_CONTENT::CMAKE_LIB]->size);

        Folder* libSrc = lib.CreateSubfolder("src/");
        libSrc->CreateSubFile(m_projects[i]->name + ".cpp", 
                m_projects[i]->fileContents[FILE_CONTENT::SRC]->content,
                m_projects[i]->fileContents[FILE_CONTENT::SRC]->size);

        Folder* libInclude = lib.CreateSubfolder("include/");
        libInclude->CreateSubFile(m_projects[i]->name + ".h", 
                m_projects[i]->fileContents[FILE_CONTENT::INCLUDE]->content,
                m_projects[i]->fileContents[FILE_CONTENT::INCLUDE]->size);
    }
    
}

void FolderManager::GenerateContents(char **projectNames, int size)
{
    std::string base(projectNames[0]);
    std::string basePath = base.substr(0, base.find_last_of("/"));
            
    PROJECT* root = new PROJECT();
    root->name = projectNames[1];
    // TODO Turn this into a function
    std::string tmp = Utils::GetTemplate(FILE_CONTENT::CMAKE_GEN, basePath);
    tmp = Utils::StringReplace(tmp, "<NAME>", projectNames[1]);
    std::cout<<tmp<<std::endl;
    root->fileContents[FILE_CONTENT::CMAKE_GEN] = new FILE_INFO(tmp.data(), tmp.size());
    //
    m_projects.push_back(root);

    PROJECT* app = new PROJECT();
    app->name = projectNames[2];
    tmp = Utils::GetTemplate(FolderManager::FILE_CONTENT::CMAKE_APP, basePath);
    tmp = Utils::StringReplace(tmp, "<NAME>", projectNames[2]);
    app->fileContents[FILE_CONTENT::CMAKE_APP] = new FILE_INFO(tmp.data(), tmp.size());

    tmp = Utils::GetTemplate(FolderManager::FILE_CONTENT::MAIN, basePath);
    app->fileContents[FILE_CONTENT::MAIN] = new FILE_INFO(tmp.data(), tmp.size());
    
    m_projects.push_back(app);

    for(int i = 3; i < size; ++i)
    {
        PROJECT* lib = new PROJECT();
        lib->name = projectNames[i];
        tmp = Utils::GetTemplate(FolderManager::FILE_CONTENT::CMAKE_LIB, basePath);
        tmp = Utils::StringReplace(tmp, "<NAME>", lib->name);
        lib->fileContents[FILE_CONTENT::CMAKE_LIB] = new FILE_INFO(tmp.data(), tmp.size());

        tmp = Utils::GetTemplate(FolderManager::FILE_CONTENT::INCLUDE, basePath);
        tmp = Utils::StringReplace(tmp, "<NAME_INCLUDE>", Utils::ToUpper(lib->name));
        tmp = Utils::StringReplace(tmp, "<NAME>", lib->name);
        lib->fileContents[FILE_CONTENT::INCLUDE] = new FILE_INFO(tmp.data(), tmp.size());

        tmp = Utils::GetTemplate(FolderManager::FILE_CONTENT::SRC, basePath);
        tmp = Utils::StringReplace(tmp, "<NAME>", lib->name);
        lib->fileContents[FILE_CONTENT::SRC] = new FILE_INFO(tmp.data(), tmp.size());

        m_projects.push_back(lib);
        
    };

    std::cout<<"success"<<std::endl;
}

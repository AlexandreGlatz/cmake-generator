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

    std::cout<<m_projects[0]->fileContents[FILE_CONTENT::CMAKE_GEN]->content<<std::endl;
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
    m_executablePath = projectNames[0];

    PROJECT* root = new PROJECT();
    root->name = projectNames[1];

    std::map<std::string, std::string> replacement = {{"<NAME>", root->name}};
    _CreateFile(root, FolderManager::FILE_CONTENT::CMAKE_GEN, replacement);

    m_projects.push_back(root);

    PROJECT* app = new PROJECT();
    app->name = projectNames[2];
    std::map<std::string, std::string> replacementApp = {{"<NAME>", app->name}};

    _CreateFile(app, FolderManager::FILE_CONTENT::CMAKE_APP, replacement);
    _CreateFile(app, FolderManager::FILE_CONTENT::MAIN);
    
    m_projects.push_back(app);

    for(int i = 3; i < size; ++i)
    {
        PROJECT* lib = new PROJECT();
        lib->name = projectNames[i];
        std::map<std::string, std::string> replacementLib = {{"<NAME>", lib->name}};

        _CreateFile(lib, FolderManager::FILE_CONTENT::CMAKE_LIB, replacementLib);
        _CreateFile(lib, FolderManager::FILE_CONTENT::SRC, replacementLib);

        replacementLib["<NAME_INCLUDE>"] = Utils::ToUpper(lib->name);
        _CreateFile(lib, FolderManager::FILE_CONTENT::INCLUDE, replacementLib);

        m_projects.push_back(lib);
    };

    std::cout<<"success"<<std::endl;
}
void FolderManager::_CreateFile(PROJECT* pProject, FILE_CONTENT type, std::map<std::string, std::string> replacements)
{    
    std::string base(m_executablePath);
    std::string basePath = base.substr(0, base.find_last_of("/"));
            
    std::string tmp = Utils::GetTemplate(type, basePath);
    for(auto const& [key, val] : replacements)
    {
        tmp = Utils::StringReplace(tmp, key, val);
    }
    pProject->fileContents[type] = new FILE_INFO(tmp.data(), tmp.size());

}


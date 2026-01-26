#include "FolderManager.h"
#include "Folder.h"
#include "File.h"
#include "Utils.h"
#include "Settings.h"
#include <iostream>
#include <sstream>

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
        Folder app(m_projects[1]->name + "/");
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

void FolderManager::GenerateContents(Settings const& settings)
{
    m_executablePath = settings.GetExecutable();
    std::map<const char*, std::vector<const char*>> projectDependencies = settings.GetProjectDependencies();
    PROJECT* root = new PROJECT();
    root->name = settings.GetRootName();

    std::stringstream rootSubdirStr;
    for(auto const& [key, value] : projectDependencies)
    {
        rootSubdirStr << "add_subdirectory(" << key << ")" << std::endl;
    }

    std::map<std::string, std::string> replacement = {{"<NAME>", root->name}, {"<SUBDIR>", rootSubdirStr.str()}};
    _CreateFile(root, FolderManager::FILE_CONTENT::CMAKE_GEN, replacement);

    m_projects.push_back(root);

    PROJECT* app = new PROJECT();
    app->name = settings.GetAppName();
    std::stringstream appDependenciesStr;
    std::vector<const char*> appDependencies = projectDependencies[settings.GetAppName()];

    for(const char* name : appDependencies)
    {
        appDependenciesStr << "target_link_libraries(${PROJECT_NAME} PRIVATE " << name <<"::library)" << std::endl;
    }
    std::map<std::string, std::string> replacementApp = {{"<NAME>", app->name}, {"<DEPENDENCIES>", appDependenciesStr.str()}};

    _CreateFile(app, FolderManager::FILE_CONTENT::CMAKE_APP, replacementApp);
    _CreateFile(app, FolderManager::FILE_CONTENT::MAIN);
    
    m_projects.push_back(app);

    for(auto const& [key, val] : projectDependencies)
    {
        if(key == app->name)
            continue;

        PROJECT* lib = new PROJECT();
        lib->name = key;

        std::stringstream libDependenciesStr;

        for(const char* name : val)
        {
            libDependenciesStr << "target_link_libraries(${PROJECT_NAME} PRIVATE " << name <<"::library)" << std::endl;
        }
        std::map<std::string, std::string> replacementLib = {{"<NAME>", lib->name}, {"<DEPENDENCIES>", libDependenciesStr.str()}};

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


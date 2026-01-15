#include "FolderManager.h"
#include "Folder.h"
#include "File.h"

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

void FolderManager::CreateArchitecture(std::string root)
{
    File cmakeGen(root + "CMakeLists.txt", 
            m_projects[0]->fileContents[FILE_CONTENT::CMAKE_GEN]->content, 
            m_projects[0]->fileContents[FILE_CONTENT::CMAKE_GEN]->size);
    Folder build(root, "build/");
    Folder resources(root, "res/");
    
    { //app
        Folder app(root, "app/");
        app.CreateSubFile("CMakeLists.txt", 
                m_projects[1]->fileContents[FILE_CONTENT::CMAKE_APP]->content,
                m_projects[1]->fileContents[FILE_CONTENT::CMAKE_APP]->size);

        Folder* appSrc = app.CreateSubfolder("src/");
        appSrc->CreateSubFile("main.cpp", 
                m_projects[1]->fileContents[FILE_CONTENT::MAIN]->content, 
                m_projects[1]->fileContents[FILE_CONTENT::MAIN]->size);
    }

    for(int i = 2; i<m_projectsAmount; ++i)
    { //lib
        Folder lib(root, "lib/");
        lib.CreateSubFile("CMakeLists.txt", 
                m_projects[i]->fileContents[FILE_CONTENT::CMAKE_LIB]->content, m_projects[i]->fileContents[FILE_CONTENT::CMAKE_LIB]->size);

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
    PROJECT* root = m_projects[0];
    m_projects[0]->name = projectNames[0]; 
    
    for(int i = 2; i<size; ++i)
    {
        
    }
}

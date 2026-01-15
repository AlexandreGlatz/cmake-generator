#ifndef _FOLDER_MANAGER_H__
#define _FOLDER_MANAGER_H__
#include <string>
#include <map>
#include <vector>

class FolderManager {
public:
    enum FILE_CONTENT {
        CMAKE_GEN,
        CMAKE_APP,
        MAIN,

        CMAKE_LIB,
        INCLUDE,
        SRC
    };

    struct FILE_INFO {
        char* content;
        int size;
    };

    struct PROJECT {
        std::string name;
        std::map<FILE_CONTENT, FILE_INFO*> fileContents;
    };

    void CreateArchitecture(std::string root);
    void GenerateContents(char** projectNames, int size);

    FolderManager(FolderManager& other) = delete;
    void operator=(const FolderManager& value) = delete;

    FolderManager* GetInstance();
private: 

    FolderManager();
    static FolderManager* m_instance;

    static void _GenerateAppProject(char* name);
    static void _GenerateLibProject(char* name);

    std::vector<PROJECT*> m_projects;
    int m_projectsAmount;
};
#endif

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

        FILE_INFO(char* _content, int _size)
        {
            content = _content, size = _size;
        }
    };

    struct PROJECT {
        std::string name;
        std::map<FILE_CONTENT, FILE_INFO*> fileContents;

        PROJECT()
        {
            name = "";
        }
    };

    void CreateArchitecture();
    void GenerateContents(char** projectNames, int size);

    FolderManager(FolderManager& other) = delete;
    void operator=(const FolderManager& value) = delete;

    static FolderManager* GetInstance();
private: 

    FolderManager();
    static FolderManager* m_instance;

    void _GenerateAppProject(char* name);
    void _GenerateLibProject(char* name);

    std::vector<PROJECT*> m_projects;
    int m_projectsAmount;
};
#endif

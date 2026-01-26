#ifndef _FOLDER_MANAGER_H__
#define _FOLDER_MANAGER_H__
#include <string>
#include <map>
#include <vector>
#include <cstring>

class Settings;
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
            content = new char[_size];
            std::memcpy(content, _content, _size);
            size = _size;
        }
    };

    struct PROJECT {
        std::string name;
        std::map<FILE_CONTENT, FILE_INFO*> fileContents;
        std::vector<char*> dependencies;

        PROJECT()
        {
            name = "";
        }
    };

    void CreateArchitecture();
    void GenerateContents(Settings const& settings);

    FolderManager(FolderManager& other) = delete;
    void operator=(const FolderManager& value) = delete;

    static FolderManager* GetInstance();
private: 

    FolderManager();
    static FolderManager* m_instance;

    void _CreateFile(PROJECT* pProject, FILE_CONTENT type, std::map<std::string, std::string> replacements = {});

    std::vector<PROJECT*> m_projects;
    std::string m_executablePath;
    int m_projectsAmount;
};
#endif

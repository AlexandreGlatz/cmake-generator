#ifndef _FOLDER_H__
#define _FOLDER_H__
#include <string>
#include <vector>

class File;
class Folder {
public:
    Folder(std::string path);
    ~Folder();

    Folder* CreateSubfolder(std::string name);
    File* CreateSubFile(std::string name, char* content, int contentSize);

private:
    void _Create();
    std::string m_path;
    std::string m_root;
};
#endif

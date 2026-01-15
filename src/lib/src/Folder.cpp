#include "Folder.h"
#include <filesystem>
#include "File.h"

Folder::Folder(std::string path, std::string root) :
    m_path(path),
    m_root(root)
{
    _Create();
}

void Folder::_Create()
{
    std::filesystem::current_path(m_root);
    std::filesystem::create_directory(m_path);
}

Folder* Folder::CreateSubfolder(std::string name)
{
    Folder* newFolder = new Folder(m_root + m_path, name);
    return newFolder;
}

File* Folder::CreateSubFile(std::string name, char *content, int contentSize)
{
    File* newFile = new File(m_root + m_path + name, content, contentSize);
    return newFile;
}

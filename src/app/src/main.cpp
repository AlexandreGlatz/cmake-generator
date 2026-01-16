#include "FolderManager.h"
#include <filesystem>
int main(int argc, char* argv[])
{
    FolderManager* pFolderManager = FolderManager::GetInstance();
    pFolderManager->GenerateContents(argv, argc);
    pFolderManager->CreateArchitecture();
}

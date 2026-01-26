#include "FolderManager.h"
#include "Settings.h"
#include <filesystem>
#include <iostream>

int main(int argc, char* argv[])
{
    Settings settings(argc, argv);
    settings.Parse();

    FolderManager* pFolderManager = FolderManager::GetInstance();
    pFolderManager->GenerateContents(settings);
    pFolderManager->CreateArchitecture();
}

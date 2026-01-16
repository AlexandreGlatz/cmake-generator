#include "File.h"
#include <fstream>
#include <iostream>

File::File(std::string path, char* content, int contentSize)
{
    _Create(path, content, contentSize);
}

File::~File()
{
}

void File::_Create(std::string path, char* content, int contentSize)
{
    std::fstream s(path, std::ios::out);
    s.write(content, contentSize);
}

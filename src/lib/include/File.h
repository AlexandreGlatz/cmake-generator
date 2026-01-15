#ifndef _FILE_H__
#define _FILE_H__
#include <string>

class File {
public:
    File(std::string path, char* content, int contentSize);
    ~File();
    

private:
    void _Create(std::string path, char* content, int contentSize);
};
#endif

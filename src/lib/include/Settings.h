#ifndef _SETTINGS_H__
#define _SETTINGS_H__

#include <vector>
#include <map>
class Settings {
public:
    Settings(int argc, char** argv);
    ~Settings();
    
    std::map<char*, std::vector<char*>> Parse();

private:
    std::vector<char*> _GetDependencies(int argc, char** argv, int index);
    int m_argc;
    char** m_argv;

};
#endif

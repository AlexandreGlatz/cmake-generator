#ifndef _SETTINGS_H__
#define _SETTINGS_H__

#include <vector>
#include <map>
#include <string>
class Settings {
public:
    Settings(int argc, char** argv);
    ~Settings();
    
    void Parse();

    std::map<const char*, std::vector<const char*>> GetProjectDependencies() { return m_projectDependencies; }
    const char* GetExecutable() { return m_executable; }
    const char* GetRootName() { return m_rootName; }

private:
    std::vector<const char*> _GetDependencies(int argc, char** argv, int index);
    int m_argc;
    char** m_argv;

private:
    std::map<const char*, std::vector<const char*>> m_projectDependencies;
    const char* m_executable;
    const char* m_rootName;

};
#endif

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

    std::map<const char*, std::vector<const char*>> GetProjectDependencies() const { return m_projectDependencies; }
    const char* GetExecutable() const { return m_executable; }
    const char* GetRootName() const { return m_rootName; }
    const char* GetAppName() const { return m_appName; }

private:
    void _CreateDependencies(int& index);
    int m_argc;
    char** m_argv;

private:
    std::map<const char*, std::vector<const char*>> m_projectDependencies;
    const char* m_executable;
    const char* m_rootName;
    const char* m_appName;

};
#endif

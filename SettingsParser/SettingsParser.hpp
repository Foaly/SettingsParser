#ifndef SETTINGSPARSER_INCLUDE
#define SETTINGSPARSER_INCLUDE

#include <string>
#include <map>

class SettingsParser 
{
public:
    SettingsParser();
    ~SettingsParser();

    bool loadFromFile(const std::string& filename);
    bool saveToFile();

    bool isChanged() const;

    void get(const std::string& key, std::string &value) const;
    void get(const std::string& key, bool &value) const;
    void get(const std::string& key, char &value) const;
    void get(const std::string& key, int &value) const;
    void get(const std::string& key, float &value) const;

    void set(const std::string& key, const std::string value);
    void set(const std::string& key, const char* value);
    void set(const std::string& key, const bool value);
    void set(const std::string& key, const char value);
    void set(const std::string& key, const int value);
    void set(const std::string& key, const float value);

    void print() const;


private:
    bool read();
    bool write() const;

    bool m_isChanged;
    std::string m_filename;
    std::map<std::string, std::string> m_data;
};

#endif // SETTINGSPARSER_INCLUDE
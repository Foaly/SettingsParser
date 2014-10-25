
#ifndef SETTINGSPARSER_INCLUDE
#define SETTINGSPARSER_INCLUDE

#include <string>
#include <map>
#include <vector>
#include <sstream>

class SettingsParser 
{
public:
    SettingsParser();
    ~SettingsParser();

    bool loadFromFile(const std::string& filename);
    bool saveToFile();

    bool isChanged() const;
    
    template<typename T>
    void get(const std::string& key, T & value) const;
    template<typename T>
    void get(const std::string& key, std::vector<T> &value) const;
    
    template<typename T>
    void set(const std::string &key, const T value);
    template<typename T>
    void set(const std::string& key, const std::vector<T> value);

    void print() const;

private:
    
    //return the string in the type of T
    template<typename T>
    T convertToType(const std::string &input) const;
    //return string of type T
    template<typename T>
    std::string convertToStr(const T input) const;
    
    bool read();
    bool write() const;
    std::pair<std::string, std::string> parseLine(const std::string &line) const;

    bool m_isChanged;
    std::string m_filename;
    std::map<std::string, std::string> m_data;
    const std::locale m_locale;
};


template<typename T>
inline std::string SettingsParser::convertToStr(T input) const {
    throw "Unsupported type supplied, either change types, or write a correct conversion function for the template type.";
}

template<>
inline std::string SettingsParser::convertToStr<std::string>(std::string value) const {
    return value;
}

template<>
inline std::string SettingsParser::convertToStr<const char*>(const char* value) const {
    return std::string(value);
}

template<>
inline std::string SettingsParser::convertToStr<bool>(bool value) const {
    return (value) ? "TRUE" : "FALSE";
}

template<>
inline std::string SettingsParser::convertToStr<char>(char value) const {
    std::string tmp = "";
    tmp = value;
    return tmp;
}

template<>
inline std::string SettingsParser::convertToStr<int>(int value) const {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template<>
inline std::string SettingsParser::convertToStr<float>(float value) const {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template<>
inline std::string SettingsParser::convertToStr<short>(short value) const {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template<>
inline std::string SettingsParser::convertToStr<double>(double value) const {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template <typename T>
inline T SettingsParser::convertToType(const std::string &input) const {
    throw "Unconvertable type encountered, please use a different type, or define the handle case in SettingsParser.hpp";
}

template<>
inline int SettingsParser::convertToType<int>(const std::string &input) const {
    int value;
    std::stringstream ss(input);
    ss >> value;
    
    return value;
}

template<>
inline double SettingsParser::convertToType<double>(const std::string &input) const {
    double value;
    std::stringstream ss(input);
    ss >> value;
    
    return value;
}

template<>
inline float SettingsParser::convertToType<float>(const std::string &input) const {
    float value;
    std::stringstream ss(input);
    ss >> value;
    
    return value;
}

template<>
inline short SettingsParser::convertToType<short>(const std::string &input) const {
    short value;
    std::stringstream ss(input);
    ss >> value;
    
    return value;
}

template<>
inline bool SettingsParser::convertToType<bool>(const std::string &input) const {
    return input == "TRUE" ? true : false;
}

template<>
inline char SettingsParser::convertToType<char>(const std::string &input) const {
    return input[0];
}

template<>
inline std::string SettingsParser::convertToType<std::string>(const std::string &input) const {
    return input;
}

template<typename T>
inline void SettingsParser::get(const std::string& key, T &value) const {
    std::map<std::string, std::string>::const_iterator it = m_data.find(key);
    
    if (it != m_data.end()){
        value = convertToType<T>(it->second);
    }
}

template<typename T>
inline void SettingsParser::get(const std::string& key, std::vector<T> &value) const {
    std::map<std::string, std::string>::const_iterator it = m_data.find(key);
    if (it != m_data.end()){
        
        std::string output;
        std::istringstream parser(it->second);
        
        unsigned int index = 0;
        
        //split by comma
        while (getline(parser, output, ',')){
            
            if (index < value.size())
                value.at(index) = convertToType<T>(output);
            else
                value.push_back(convertToType<T>(output));
            
            ++index;
        }
    }
}

template<typename T>
inline void SettingsParser::set(const std::string& key, const T value) {
    std::map<std::string, std::string>::iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        it->second = convertToStr<T>(value);
        m_isChanged = true;
    }
}

template<typename T>
inline void SettingsParser::set(const std::string &key, const std::vector<T> value) {
    std::map<std::string, std::string>::iterator it = m_data.find(key);
    
    if (it != m_data.end()) {
        
        std::string setString;
        for (int i = 0; i < value.size() - 1; ++i){
            setString += convertToStr<T>(value.at(i)) + ",";
        }
        setString += convertToStr<T>(value.back());
        
        it->second = setString;
        m_isChanged = true;
    }
}

#endif // SETTINGSPARSER_INCLUDE

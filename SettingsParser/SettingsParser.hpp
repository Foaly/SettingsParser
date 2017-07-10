////////////////////////////////////////////////////////////
// Copyright (c) 2016 Maximilian Wagenbach
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgement in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
////////////////////////////////////////////////////////////


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
inline std::string SettingsParser::convertToStr<unsigned int>(unsigned int value) const {
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
inline unsigned int SettingsParser::convertToType<unsigned int>(const std::string &input) const {
    unsigned int value;
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
    auto it = m_data.find(key);

    if (it != m_data.end()){
        value = convertToType<T>(it->second);
    }
}

/**
 * This method tries to read the value of a key into a vector. The values have to be
 * seperated by comma. The vector is cleared before it is filled.
 */
template<typename T>
inline void SettingsParser::get(const std::string& key, std::vector<T> &value) const {
    auto it = m_data.find(key);
    if (it != m_data.end()){

        std::string output;
        std::istringstream parser(it->second);

        value.clear();

        //split by comma
        while (getline(parser, output, ',')){
            value.push_back(convertToType<T>(output));
        }
    }
}

template<typename T>
inline void SettingsParser::set(const std::string& key, const T value) {
    // the [] operator replaces the value if the key is found, if not it creates a new element
    m_data[key] = convertToStr<T>(value);
    m_isChanged = true;
}

template<typename T>
inline void SettingsParser::set(const std::string &key, const std::vector<T> value) {
    // transform the vector into a string that seperates the elements with a comma
    std::string valueAsString;
    for (size_t i = 0; i < value.size() - 1; ++i){
        valueAsString += convertToStr<T>(value.at(i)) + ",";
    }
    valueAsString += convertToStr<T>(value.back());

    // the [] operator replaces the value if the key is found, if not it creates a new element
    m_data[key] = valueAsString;
    m_isChanged = true;
}

#endif // SETTINGSPARSER_INCLUDE

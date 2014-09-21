#include "SettingsParser.hpp"

#include <locale>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


SettingsParser::SettingsParser() : m_isChanged(false)
{

}


SettingsParser::~SettingsParser()
{
    saveToFile();
}


bool SettingsParser::loadFromFile(const std::string& filename)
{
    m_data.clear();
    m_filename = filename;
    return read();
}


bool SettingsParser::saveToFile()
{
    if(m_isChanged)
    {
        m_isChanged = false;
        return write();
    }
    return true;
}


bool SettingsParser::read()
{
    std::ifstream in(m_filename);
    if(!in.is_open())
    {
        std::cerr << "Error: Unable to open settings file: \"" << m_filename << "\" for reading!" << std::endl;
        return false;
    }
    std::string line;
    const std::locale loc;
    while(std::getline(in, line))
    {
        // parse line
        if(line.size() > 0 && line[0] != '#')
        {
            size_t j = 0;
            // trim leading whitespace
            while(std::isspace(line[j], loc))
                j++;
            // get the key string
            const int beginKeyString = j;
            while(!std::isspace(line[j], loc))
                j++;
            const std::string key = line.substr(beginKeyString, j - beginKeyString);

            // skip the assignment
            while(std::isspace(line[j], loc) || line[j] == '=')
                j++;
            
            // get the value string
            const std::string value = line.substr(j, line.size() - j);

            m_data[key] = value;
        }
    }
    in.close();
    m_isChanged = false;
    return true;
}


bool SettingsParser::write() const
{
    std::vector<std::pair<std::string, std::string> > fileContents;

    std::ifstream in(m_filename);
    if(in.is_open())
    {
        std::string line, key, value;
        const std::locale loc;
        while(std::getline(in, line))
        {
            // parse line
            if(line.size() > 0 && line[0] != '#')
            {
                size_t j = 0;
                // trim leading whitespace
                while(std::isspace(line[j], loc))
                    j++;
                // get the key string
                const int beginKeyString = j;
                while(!std::isspace(line[j], loc))
                    j++;
                key = line.substr(beginKeyString, j - beginKeyString);

                // check if the key is found in the map
                std::map<std::string, std::string>::const_iterator it = m_data.find(key);
                if (it != m_data.end())
                {
                    // if so take it's value
                    value = it->second;
                }
                else
                {
                    // if not get the value string from the file

                    // skip the assignment
                    while(std::isspace(line[j], loc) || line[j] == '=')
                        j++;
                
                    // get the value string
                    value = line.substr(j, line.size() - j);
                }
            }
            else
            {
                key = line;
                value = "";
            }
            fileContents.push_back(std::make_pair(key, value));
        }
    }
    else
    {
        // Can't open file for reading. Use only the data from the map
        for (std::map<std::string, std::string>::const_iterator it = m_data.begin(); it != m_data.end(); ++it)
            fileContents.push_back(std::make_pair(it->first, it->second));
    }

    in.close();



    // open the file for writing
    std::ofstream out(m_filename);
    if(!out.is_open())
    {
        std::cerr << "Error: Unable to open settings file: \"" << m_filename << "\" for writing!" << std::endl;
        return false;
    }
    for (std::vector<std::pair<std::string, std::string> >::const_iterator it = fileContents.begin() ; it != fileContents.end(); ++it)
    {
        if(it->first[0] == '#' || it->first[0] == 0)
            out << it->first << std::endl;
        else
            out << it->first << " = " << it->second << std::endl;
    }
    out.close();
    return true;
}


void SettingsParser::print() const
{
    for(auto& element: m_data)
        std::cout << element.first << " = " << element.second<< std::endl;

    std::cout << std::endl << "Size: " << m_data.size() << std::endl;
}


bool SettingsParser::isChanged() const
{
    return m_isChanged;
}


void SettingsParser::get(const std::string& key, std::string &value) const
{
    std::map<std::string, std::string>::const_iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        value = it->second;
    }
}


void SettingsParser::get(const std::string& key, bool &value) const
{
    std::map<std::string, std::string>::const_iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        value = ((it->second == "TRUE") ? true : false);
    }
}


void SettingsParser::get(const std::string& key, char &value) const
{
    std::map<std::string, std::string>::const_iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        value = it->second[0];
    }
}


void SettingsParser::get(const std::string& key, int &value) const
{
    std::map<std::string, std::string>::const_iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        std::stringstream ss(it->second);
        ss >> value;
    }
}


void SettingsParser::get(const std::string& key, float &value) const
{
    std::map<std::string, std::string>::const_iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        std::stringstream ss(it->second);
        ss >> value;
    }
}


void SettingsParser::set(const std::string& key, const std::string value)
{
    std::map<std::string, std::string>::iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        it->second = value;
        m_isChanged =  true;
    }                                 
}

void SettingsParser::set(const std::string& key, const char* value)
{
    std::map<std::string, std::string>::iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        it->second = std::string(value);
        m_isChanged =  true;
    }                                 
}


void SettingsParser::set(const std::string& key, const bool value)
{
    std::map<std::string, std::string>::iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        it->second = (value) ? "TRUE" : "FALSE";
        m_isChanged =  true;
    }
}


void SettingsParser::set(const std::string& key, const char value)
{
    std::map<std::string, std::string>::iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        std::string tmp = "";
        tmp = value;
        it->second = tmp;
        m_isChanged =  true;
    }
}


void SettingsParser::set(const std::string& key, const int value)
{
    std::map<std::string, std::string>::iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        std::stringstream ss;
        ss << value;
        it->second = ss.str();
        m_isChanged =  true;
    }
}


void SettingsParser::set(const std::string& key, const float value)
{
    std::map<std::string, std::string>::iterator it = m_data.find(key);
    if (it != m_data.end())
    {
        std::stringstream ss;
        ss << value;
        it->second = ss.str();
        m_isChanged =  true;
    }
}
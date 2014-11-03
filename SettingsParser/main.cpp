#include "SettingsParser.hpp"
#include <iostream>
#include <vector>

int main()
{
    //....

    SettingsParser settings;
    if(!settings.loadFromFile("settings.txt"))
    {
        std::cout << "Error loading settings file!" << std::endl;
        return -1;
    }

    int width = 800;
    int height = 600;
    settings.get("width", width);
    settings.get("height", height);
    // if "width" and "height" are not found in the settings file their values are untouched 
    // (meaning you can easily set defaults like shown above)

    std::string title;
    settings.get("title", title);

    float gravity;
    settings.get("g", gravity);

    char ch;
    settings.get("player", ch);

    bool fullscreen;
    settings.get("fullscreen", fullscreen);

    std::vector<int> rectangle;
    settings.get("rectangle", rectangle);
    
    //....

    std::string newTitle = "SFML Settings Parser rocks!";
    settings.set("title", "SFML Settings Parser rocks!");
    settings.saveToFile(); // this is also done in the destructor

    settings.print();
    std::cin.get();

    return 0;
}

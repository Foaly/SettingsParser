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

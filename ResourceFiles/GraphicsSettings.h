#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H

#include "../includes.h"

class GraphicsSettings
{
public:
    GraphicsSettings();

    // Variables
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    // functions

    void SaveToFile(std::string path);

    void LoadFromFile(std::string path);
};

#endif // GRAPHICSSETTINGS_H
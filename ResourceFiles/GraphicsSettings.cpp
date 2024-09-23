#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
    this->title = "DEFAULT";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->verticalSync = false;
    this->frameRateLimit = 60;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
}

// Functions
void GraphicsSettings::SaveToFile(std::string path)
{
    std::ofstream ofs(path);

    if (ofs.is_open())
    {
        ofs << this->title;
        ofs << this->resolution.width << " " << this->resolution.height;
        ofs << this->fullscreen;
        ofs << this->frameRateLimit;
        ofs << this->verticalSync;
        ofs << contextSettings.antialiasingLevel;
        // define the resolution of workspace
    }

    ofs.close();
}

void GraphicsSettings::LoadFromFile(std::string path)
{
    std::ifstream ifs(path);

    if (ifs.is_open())
    {
        //foi usado getline nessa parte porque o operador >> captura apenas palavrase se o titulo
        //do jogo tiver espaço ele captura apenas a primeira palavra
        std::getline(ifs, this->title);
        ifs >> this->resolution.width >> this->resolution.height;
        ifs >> this->fullscreen;
        ifs >> this->frameRateLimit;
        ifs >> this->verticalSync;
        ifs >> contextSettings.antialiasingLevel;
        // define the resolution of workspace
    }

    ifs.close();
}

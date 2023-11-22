#ifndef GAME_H
#define GAME_H
//general includes

//includes do game
#include "../StateFiles/MainMenuState.h"
#include "../StateFiles/GameState.h"

class Game
{
private:

    class GraphicsSettings
    {
    public:
        GraphicsSettings()
        {
            this->title = "DEFAULT";
            this->resolution = sf::VideoMode::getDesktopMode();
            this->fullscreen = false;
            this->verticalSync = false;
            this->frameRateLimit = 60;
            this->contextSettings.antialiasingLevel = 0;
            this->videoModes = sf::VideoMode::getFullscreenModes(); 
        }

        //Variables
        std::string title;
        sf::VideoMode resolution;
        bool fullscreen;
        bool verticalSync;
        unsigned frameRateLimit;
        sf::ContextSettings contextSettings;
        std::vector<sf::VideoMode> videoModes;


        //functions

        void SaveToFile(std::string path)
        {
            std::ofstream ofs(path);

            if(ofs.is_open())
            {
                ofs << this->title;
                ofs << this->resolution.width << " " << this->resolution.height;
                ofs << this->fullscreen;
                ofs << this->frameRateLimit;
                ofs << this->verticalSync;
                ofs << contextSettings.antialiasingLevel;
                //define the resolution of workspace
                
            }
            ofs.close();
        }

        void LoadFromFile(std::string path)
        {
            std::ifstream ifs(path);
            

            if(ifs.is_open())
            {
                std::getline(ifs, this->title);
                ifs >> this->resolution.width >> this->resolution.height;
                ifs >> this->fullscreen;
                ifs >> this->frameRateLimit;
                ifs >> this->verticalSync;
                ifs >> contextSettings.antialiasingLevel;
                //define the resolution of workspace
                
            }
            ifs.close();
        }
    };
    
    GraphicsSettings gfxSettings;
    sf::RenderWindow * window;
    sf::Event event;
 
    float dt;
    sf::Clock dtClock;

    std::stack <State*> states;
    std::map <std::string, int> supportedKeys;
    
    //fucntions
    void initVariables();
    void initGraphicsSettings();
    void initGameWindow();
    void initStates();
    void initKeys();
public:
    Game();
    virtual ~Game();
    //regular
    void endApplication();
    //update
    void dtUpdate();
    void updateSFMLEvents();
    void update();
    //render
    void render();
    //core
    void run();

};

#endif //GAME_H
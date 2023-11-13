#ifndef GAME_H
#define GAME_H
//general includes

//includes do game
#include "../StateFiles/MainMenuState.h"
#include "../StateFiles/GameState.h"

class Game
{
private:
    sf::RenderWindow * window;
    sf::Event event;
    sf::ContextSettings window_settings;
    std::vector<sf::VideoMode> videoMods;
    bool fullscreen;
    float dt;
    sf::Clock dtClock;

    std::stack <State*> states;
    std::map <std::string, int> supportedKeys;
    
    //fucntions
    void initVariables();
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
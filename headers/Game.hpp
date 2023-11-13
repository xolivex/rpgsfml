#ifndef Game_hpp
#define Game_hpp
//general includes

//includes do game
#include "GameState.hpp"
#include "State.hpp"

class Game
{
private:
    sf::RenderWindow * window;
    sf::Event event;
    sf::Clock dtClock;
    std::stack <State*> states;
    std::map <std::string, int> supportedKeys;
    float dt;
    //fucntions
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

#endif
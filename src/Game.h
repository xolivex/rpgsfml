#ifndef GAME_H
#define GAME_H
// general includes

// includes do game
#include "../StateFiles/MainMenuState.h"
#include "../StateFiles/GameState.h"
#include "../ResourceFiles/GraphicsSettings.h"

class Game
{
private:
    GraphicsSettings gfxSettings;
    StateData stateData;
    sf::RenderWindow *window;
    sf::Event event;

    float dt;
    sf::Clock dtClock;

    std::stack<State *> states;
    std::map<std::string, int> supportedKeys;

    float gridSize;

    // fucntions
    void initVariables();
    void initGraphicsSettings();
    void initGameWindow();
    void initStateData();
    void initStates();
    void initKeys();

public:
    Game();
    virtual ~Game();
    // regular
    void endApplication();
    // update
    void dtUpdate();
    void updateSFMLEvents();
    void update();
    // render
    void render();
    // core
    void run();
};

#endif // GAME_H
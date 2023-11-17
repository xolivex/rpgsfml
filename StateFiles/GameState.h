#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "State.h"
#include "../GUI/PauseMenu.h"
class GameState : public State
{
private:
    //variables
    Player * player;
    PausedMenu * pmenu;
    sf::Font font;
    //Functions
    void initKeybinds();
    void initTextures();
    void initPlayers();
    void initPausedMenu();
    void initFonts();
public:
    GameState(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys, std::stack<State*> * states);
    virtual ~GameState();

    //functions
    void updateInput(const float& dt);
    void updatePlayerInput(const float & dt);
    void update(const float& dt);
    void render(sf::RenderTarget * target = nullptr);
};

#endif //GAME_STATE_H
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "../GUI/PauseMenu.h"
#include "../Tile/TileMap.h"

class GameState : public State
{
private:
    //variables
    Player * player;
    PausedMenu * pmenu;
    sf::Font font;
    TileMap map;

    //Functions
    void initKeybinds();
    void initTextures();
    void initPlayers();
    void initPausedMenu();
    void initFonts();
public:
    GameState(StateData * state_data);
    virtual ~GameState();

    //functions
    void updateInput(const float& dt);
    void updatePlayerInput(const float & dt);
    void update(const float& dt);
    void render(sf::RenderTarget * target = nullptr);
};

#endif //GAME_STATE_H
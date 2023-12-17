#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "../GUI/PauseMenu.h"
#include "../Tile/TileMap.h"



class Player;
class PauseMenu;
class TileMap;

class GameState : public State
{
private:
    //variables
    Player * player;
    PausedMenu * pmenu;
    sf::Font font;
    TileMap * tileMap;

    sf::View view;

    //Functions
    void initView();
    void initKeybinds();
    void initTextures();
    void initPlayers();
    void initPausedMenu();
    void initFonts();
    void initTileMap();
public:
    GameState(StateData * state_data);
    virtual ~GameState();

    //functions
    void updateView(const float& dt);
    void updateTileMap();
    void updateInput(const float& dt);
    void updatePlayerInput(const float & dt);
    void update(const float& dt);
    void renderTileMap(sf::RenderTarget & target);
    void render(sf::RenderTarget * target = nullptr);
};

#endif //GAME_STATE_H
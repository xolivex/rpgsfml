#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "../GUI/PauseMenu.h"
#include "../Tile/TileMap.h"



class PauseMenu;
class TileMap;
//class PlayerGUI;

class GameState : public State
{
private:
    //variables
    Player * player;
    PlayerGUI * playerGui;
    PausedMenu * pmenu;
    sf::Font font;
    TileMap * tileMap;

    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    //Functions
    void initDeferredRender();
    void initView();
    void initKeybinds();
    void initTextures();
    void initPlayers();
    void initPausedMenu();
    void initFonts();
    void initTileMap();
    void initplayerGui();
public:
    GameState(StateData * state_data);
    virtual ~GameState();

    //functions
    void updateView(const float& dt);
    void updateTileMap(const float & dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float & dt);
    void update(const float& dt);
    void renderTileMap(sf::RenderTarget & target);
    void render(sf::RenderTarget * target = nullptr);
};

#endif //GAME_STATE_H
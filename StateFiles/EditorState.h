#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "../ResourceFiles/Gui.h"
#include "../Tile/TileMap.h"
#include "../GUI/PauseMenu.h"

class State;
class Gui;
class TileMap;
class PauseMenu;


class EditorState  : public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    PausedMenu * pmenu;

    TileMap * tileMap;
    
    std::map<std::string, gui::Button*> buttons;

    sf::RectangleShape selectorRect;

    //Functions
    void initVariables();
    void initBackground();
    void initKeybinds();
    void initFonts();
    void initButtons();
    void initPausedMenu();
    void initTileMap();
    void initGui();
public:
    EditorState(StateData * state_data);
    virtual ~EditorState();

    //functions
    void updateEditorInput(const float & dt);
    void updateInput(const float & dt);
    void updateGui();
    void updateButtons();
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget * target = NULL);
};


#endif //EDITORSTATE_H
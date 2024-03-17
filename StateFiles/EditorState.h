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
    sf::View view;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text cursorText;
    std::stringstream ss;
    PausedMenu * pmenu;

    TileMap * tileMap;
    
    std::map<std::string, gui::Button*> buttons;

    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;
    sf::RectangleShape sidebar;
    gui::TextureSelector * textureSelector;

    bool collision = false;
    short type = Typetile::DEFAULT;
    float viewspeed;

    //init Functions
    void initView();
    void initVariables();
    void initBackground();
    void initKeybinds();
    void initFonts();
    void initText();
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
    void updateGui(const float &dt);
    void updateButtons();
    void updateMap(const float &dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget * target = NULL);
};


#endif //EDITORSTATE_H
#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "../ResourceFiles/Gui.h"
#include "../Tile/TileMap.h"
#include "../GUI/PauseMenu.h"

class EditorState  : public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    PausedMenu * pmenu;

    TileMap map;
    
    std::map<std::string, gui::Button*> buttons;

    //Functions
    void initVariables();
    void initBackground();
    void initKeybinds();
    void initFonts();
    void initButtons();
    void initPausedMenu();
    void initMap();
public:
    EditorState(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys, std::stack<State*> * states);
    virtual ~EditorState();

    //functions
    void updateInput(const float & dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget * target = NULL);
};


#endif //EDITORSTATE_H
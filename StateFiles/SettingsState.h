#ifndef SETTINSSTATE_H
#define SETTINSSTATE_H
#include "State.h"
#include <iostream>
#include "../ResourceFiles/Gui.h"

class SettingsState : public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    
    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;

    //Functions
    void initVariables();
    void initBackground();
    void initKeybinds();
    void initFonts();
    void initGui();
public:
    SettingsState(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys, std::stack<State*> * states);
    virtual ~SettingsState();

    //functions
    void updateInput(const float & dt);
    void updateGui(const float & dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget * target = NULL);
};


#endif //SETTINSSTATE_H


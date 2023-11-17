#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "../ResourceFiles/Button.h"

class PausedMenu
{
private:
    
    sf::RectangleShape background;
    sf::RectangleShape container;
    sf::Text text;
    sf::Font& font;

    std::map<std::string, Button*> buttons;
    //Functions 
    void initText();
public:
    PausedMenu(sf::RenderWindow& window, sf::Font& font);
    virtual ~PausedMenu();

    //Functions
    std::map<std::string, Button*>& getButtons();
    const bool isPressed(const std::string key);
    void addButton(const std::string key, float y, const std::string text);
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget & target);
};

#endif //PAUSEMENU_H
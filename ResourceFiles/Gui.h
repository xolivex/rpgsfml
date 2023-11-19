#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{

class Button
{
private:
    short unsigned buttonState;

    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
public:
    Button(float x, float y, float width, float height, sf::Font * font, std::string text, unsigned short character_size,
        sf::Color text_idle_color, sf::Color text_hover_color,sf::Color text_active_color,
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    ~Button();
    //Acessors
    const bool isPressed() const;
    const std::string getText() const;

    //Modifiers
    void setText(const std::string text);
    //Functions
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget& target);
    
};

class DropDownList
{
private:
    float keytime;
    float keytimeMax;

    sf::Font& font;
    gui::Button* activeElement;
    std::vector<gui::Button*> list;
    bool showList;

public:
    DropDownList(
        float x, float y, float width, float height,
        sf::Font& font, std::string list[],
        unsigned short numbElements, unsigned short default_index = 0);
    ~DropDownList();
    //Accessors
    const bool getkeyTime();

    void updatekeyTime(const float& dt);
    void update(const sf::Vector2f& mousePos, const float& dt);
    void render(sf::RenderTarget& target);
};
}
#endif //BUTTON_H
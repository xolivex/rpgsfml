#ifndef BUTTON_H
#define BUTTON_H

#include "../includes.h"

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{

class Button
{
private:
    int buttonState;
    int id;

    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

    sf::Color outlineIdleColor;
    sf::Color outlineHoverColor;
    sf::Color outlineActiveColor;
public:
    Button(float x, float y, 
        float width, float height, 
        sf::Font * font, 
        std::string text, 
        int character_size,
        sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
        sf::Color outline_idle_color = sf::Color::Transparent, 
        sf::Color outline_hover_color = sf::Color::Transparent,
        sf::Color outline_active_color = sf::Color::Transparent, 
        int id = 0
        );
    ~Button();
    //Acessors
    const bool isPressed() const;
    const std::string getText() const;
    const int & getId() const;

    //Modifiers
    void setText(const std::string text);
    void setId(unsigned short id);
    //Functions
    void update(const sf::Vector2i& mousePosWindow);
    void render(sf::RenderTarget & target);
    
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
        int numbElements, int default_index = 0);
    ~DropDownList();
    //Accessors
    const int getActiveElementId() const;
    const bool getkeyTime();

    void updatekeyTime(const float& dt);
    void update(const sf::Vector2i& mousePosWindow, const float& dt);
    void render(sf::RenderTarget& target);
};

class TextureSelector
{
private:
    bool active;
    bool hidden;
    float gridSize;
    float offset;
    float keytime;
    const float keytimeMax;

    sf::RectangleShape selector;
    sf::RectangleShape bounds;
    sf::Vector2i mousePosGrid;
    sf::Sprite sheet;
    sf::IntRect textureRect;
    gui::Button * hidden_btn;
public:
    TextureSelector(float x, float y,
     float width, float height, 
     float gridSize, const sf::Texture* texture_sheet, sf::Font & font, std::string text);
    ~TextureSelector();

    //Accessors
    const bool & getActive() const;
    const sf::IntRect& getTextureRect() const;
    const bool getkeyTime();

    //Functions
    void updatekeyTime(const float& dt);
    void update(const sf::Vector2i& mousePosWindow, const float &dt);
    void render(sf::RenderTarget & target);
};
}
#endif //BUTTON_H

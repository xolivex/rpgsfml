#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, unsigned short character_size,
        sf::Color text_idle_color, sf::Color text_hover_color,sf::Color text_active_color,
        sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color)
{
    this->buttonState = BTN_IDLE;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idle_Color);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
    );

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->idleColor = idle_Color;
    this->hoverColor = hover_Color;
    this->activeColor = active_Color;

    

}

Button::~Button()
{
    
}


void Button::update(const sf::Vector2f& mousePos)
{
    /*Update the booleans for hover and pressed*/

    //idle
    this->buttonState = BTN_IDLE;

    //hover
    if(this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = BTN_HOVER;

        //pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (this->buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        this->text.setFillColor(this->textIdleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        break;
    
    default:
        this->shape.setFillColor(sf::Color::Red);
        break;
    }
}

const bool Button::isPressed() const
{
    if(this->buttonState == BTN_ACTIVE)
        return true;
    
    return false;
}

void Button::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
    target.draw(this->text);
}

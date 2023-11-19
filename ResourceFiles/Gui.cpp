#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, unsigned short character_size,
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

gui::Button::~Button()
{
    
}
//Modifiers
void gui::Button::setText(const std::string text)
{
    this->text.setString(text);
}

void gui::Button::update(const sf::Vector2f &mousePos)
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
//Accessors
const bool gui::Button::isPressed() const
{
    if(this->buttonState == BTN_ACTIVE)
        return true;
    
    return false;
}

const std::string gui::Button::getText() const
{
    return this->text.getString();
}

void gui::Button::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
    target.draw(this->text);
}

//DROPDWON LIST ==============================================================================

gui::DropDownList::DropDownList(
    float x, float y, float width, float height,
    sf::Font& font, std::string list[], unsigned short numbElements, unsigned short default_index)
    : font(font), showList(false), keytimeMax(2.f), keytime(0.f)
{
    
    for(size_t i = 0; i < numbElements; i++)
    {
        this->list.push_back(
            new gui::Button(
                x, y + (i * height), width, height,
                &this->font, list[i], 12,
                sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(20, 20, 20, 50),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200))
            );
    }
    this->activeElement = new Button(*this->list[default_index]);
}

gui::DropDownList::~DropDownList()
{
    delete this->activeElement;
    for(size_t i = 0; i < this->list.size(); i++)
    {
        delete this->list[i];
    }
}

const bool gui::DropDownList::getkeyTime()
{
    if(this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

void gui::DropDownList::updatekeyTime(const float &dt)
{
    if(this->keytime < this->keytimeMax)
        this->keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2f &mousePos, const float& dt)
{
    this->updatekeyTime(dt);
    this->activeElement->update(mousePos);
    //show and hide the list
    if(this->activeElement->isPressed() && this->getkeyTime())
    {
        if(this->showList)
        {
            this->showList = false;
        }
        else
        {
            this->showList = true;
        }
    }

    if(this->showList)
    {
        for(auto &i : this->list)
        {
            i->update(mousePos);
        }
    }
}

void gui::DropDownList::render(sf::RenderTarget &target)
{
    this->activeElement->render(target);
    if(this->showList)
    {
        for(auto &i : this->list)
        {
            i->render(target);
        }
    }
}
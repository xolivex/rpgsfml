#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, unsigned short character_size,
        sf::Color text_idle_color, sf::Color text_hover_color,sf::Color text_active_color,
        sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color,
        sf::Color outline_idle_color, sf::Color outline_hover_color,
        sf::Color outline_active_color, short unsigned id
        )
{
    this->buttonState = BTN_IDLE;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idle_Color);
    this->shape.setOutlineThickness(1.f);

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

    this->outlineIdleColor = outline_idle_color;
    this->outlineHoverColor = outline_hover_color;
    this->outlineActiveColor = outline_active_color;

    

}

gui::Button::~Button()
{
    
}
//Modifiers
void gui::Button::setText(const std::string text)
{
    this->text.setString(text);
}

void gui::Button::setId(short unsigned id)
{
    this->id = id;
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
        this->shape.setOutlineColor(this->outlineIdleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        this->shape.setOutlineColor(this->outlineHoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        this->shape.setOutlineColor(this->outlineActiveColor);
        break;
    
    default:
        this->shape.setFillColor(sf::Color::Red);
        this->text.setFillColor(sf::Color::Blue);
        this->shape.setOutlineColor(sf::Color::Green);
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

const short unsigned gui::Button::getId() const
{
    return this->id;
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
    this->activeElement = new gui::Button(
                x, y, width, height,
                &this->font, list[default_index], 12,
                sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 250), sf::Color(20, 20, 20, 50),
                sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
            );
    
    for(size_t i = 0; i < numbElements; i++)
    {
        this->list.push_back(
            new gui::Button(
                x, y + ((i+1) * height), width, height,
                &this->font, list[i], 12,
                sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(20, 20, 20, 50),
                sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
                i
                )
            );
    }
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
            if(i->isPressed() && this->getkeyTime())
            {
                this->activeElement->setText(i->getText());
                this->activeElement->setId(i->getId());
                this->showList = false;
            }
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

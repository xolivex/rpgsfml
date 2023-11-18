#include "PauseMenu.h"

std::map<std::string, gui::Button *> &PausedMenu::getButtons()
{
    return this->buttons;
}

const bool PausedMenu::isPressed(const std::string key)
{
    return this->buttons[key]->isPressed();   
}

void PausedMenu::addButton(const std::string key, float y, const std::string text)
{
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - 250.f / 2.f;

    this->buttons[key] = new gui::Button(x, y, 150.f, 50.f, &this->font, text, 50,
        sf::Color(150,150,150,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
        sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));
}

void PausedMenu::initText()
{
    this->text.setFont(this->font);
    this->text.setString("PAUSED");
    this->text.setCharacterSize(60);
    this->text.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f
    - this->text.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + 30.f);
}
//Constructor
PausedMenu::PausedMenu(sf::RenderWindow& window, sf::Font& font): font(font)
{
    this->background.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)
        )
    );
    this->background.setFillColor(sf::Color(20,20,20,100));

    this->container.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x) / 4.f,
            static_cast<float>(window.getSize().y)
        )
    );
    this->container.setFillColor(sf::Color(20,20,20,200));
    this->container.setPosition(
        static_cast<float>(window.getSize().x) / 2.f - this->container.getGlobalBounds().width / 2.f,
        0.f
    );
    initText();
}
//Destructor
PausedMenu::~PausedMenu()
{
    auto it = this->buttons.begin();
    for(it = this->buttons.begin();it != this->buttons.end(); ++it)
    {
        delete it->second;
    }   
}


void PausedMenu::update(const sf::Vector2f& mousePos)
{
    for(auto &i : this->buttons)
    {
        i.second->update(mousePos);
    }
}

void PausedMenu::render(sf::RenderTarget &target)
{
    target.draw(background);
    target.draw(container);
    target.draw(text);

    for(auto &i : buttons)
    {
        i.second->render(target);
    }
}

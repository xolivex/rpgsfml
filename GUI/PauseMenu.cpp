#include "PauseMenu.h"

void PausedMenu::initText()
{
    this->text.setFont(this->font);
    this->text.setString("PAUSED");
    this->text.setCharacterSize(60);
    this->text.setPosition(this->container.getPosition().x + 
        this->container.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f,
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


void PausedMenu::update()
{
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

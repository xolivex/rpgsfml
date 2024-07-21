#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
    this->font.loadFromFile("Config/gamestate_keybinds.ini");

}

void PlayerGUI::initHpBar()
{
    this->hpBarBack.setSize(sf::Vector2f(100.f, 20.f));
    this->hpBarBack.setFillColor(sf::Color(50, 50, 200, 255));
    this->hpBarBack.setPosition(20.f, 20.f);

    this->hpBarInner.setSize(sf::Vector2f(100.f, 20.f));
    this->hpBarInner.setFillColor(sf::Color(250, 50, 200, 255));
    this->hpBarInner.setPosition(this->hpBarBack.getPosition());
}

PlayerGUI::PlayerGUI(Player *player)
{
    this->player = player;

    this->initFont();
    this->initHpBar();
}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::updateHpBar()
{
}

void PlayerGUI::renderHpBar(sf::RenderTarget & target)
{
    target.draw(this->hpBarBack);
    target.draw(this->hpBarInner);
}

void PlayerGUI::update(const float &dt)
{
}

void PlayerGUI::render(sf::RenderTarget & target)
{
    this->renderHpBar(target);
}

#include "../headers/GameState.hpp"


void GameState::initKeybinds()
{
    this->Keybinds.emplace("MOVE_LEFT", this->supportedKeys->at("A"));
    this->Keybinds.emplace("MOVE_RIGHT", this->supportedKeys->at("D"));
    this->Keybinds.emplace("MOVE_UP", this->supportedKeys->at("W"));
    this->Keybinds.emplace("MOVE_DOWN", this->supportedKeys->at("S"));
}
GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys)
    : State(window, supportedKeys)
{
    this->initKeybinds();
}
GameState::~GameState()
{
    
}

void GameState::endState()
{
    std::cout << "Ending GameState!" << "\n";
}

void GameState::updateInput(const float &dt)
{
    this->checkForQuit();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_LEFT"))))
    {
        this->player.move(dt, -1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_RIGHT"))))
    {
        this->player.move(dt, 1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_UP"))))
    {
        this->player.move(dt, 0.f, -1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_DOWN"))))
    {
        this->player.move(dt, 0.f, 1.f);
    }
}


void GameState::update(const float & dt)
{
    this->updateInput(dt);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        std::cout << "A" << "\n";

    this->player.update(dt);
}

void GameState::render(sf::RenderTarget * target)
{
    if(!target)
    {
        target = this->window;
    }
    this->player.render(target);
}

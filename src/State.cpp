#include "../headers/State.hpp"

State::State(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys)
{
    this->window = window;
    this->quit = false;
    this->supportedKeys = supportedKeys;
}

State::~State()
{

}

const bool & State::getQuit() const 
{
    return this->quit;
}

void State::checkForQuit()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->quit = true;
    }
}
#include "State.h"

State::State(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys, std::stack<State*> * states)
{
    this->window = window;
    this->quit = false;
    this->supportedKeys = supportedKeys;
    this->states = states;
}

State::~State()
{

}

const bool & State::getQuit() const 
{
    return this->quit;
}

void State::endState()
{
        this->quit = true;
}

void State::unpausedState()
{
    this->paused = false;
}

void State::pausedState()
{
    this->paused = true;
}

void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

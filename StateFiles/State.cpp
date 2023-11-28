#include "State.h"

State::State(StateData * state_data)
{
    this->stateData = state_data;
    this->window = state_data->window;
    this->quit = false;
    this->supportedKeys = state_data->supportedKeys;
    this->states = state_data->states;
    this->keytime = 0.f;
    this->keytimeMax = 10.f;
    this->gridSize = state_data->gridSize;
}

State::~State()
{

}

const bool & State::getQuit() const 
{
    return this->quit;
}

const bool State::getKeytime()
{
    if(this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
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

void State::updateKeytime(const float& dt)
{
    if(this->keytime < this->keytimeMax)
    {
        this->keytime += 50.f * dt;
    }
}

void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    this->mousePosGrid = sf::Vector2u(
        //the conversion for unsigned it happanes inside of class Vector2u
        /*static_cast<unsigned>(*/this->mousePosView.x/*)*/ / /*static_cast<unsigned>(*/this->gridSize/*)*/,
        /*static_cast<unsigned>(*/this->mousePosView.y/*)*/ / /*static_cast<unsigned>(*/this->gridSize/*)*/
    );
    std::cout << this->mousePosGrid.x << " . " << this->mousePosGrid.y <<"\n";
}

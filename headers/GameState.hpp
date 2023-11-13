#ifndef GameState_hpp
#define GameState_hpp

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Entity.hpp"
#include <iostream>

class GameState : public State{
private:
    Entity player;
    //Functions
    void initKeybinds();
public:
    GameState(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys);
    virtual ~GameState();

    //functions
    void endState();
    void updateInput(const float & dt);
    void update(const float& dt);
    void render(sf::RenderTarget * target = nullptr);
};

#endif
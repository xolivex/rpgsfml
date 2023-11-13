#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>

#include "../entities/Player.h"

class State{
private:

protected:
    std::stack<State*> * states;
    sf::RenderWindow * window;
    std::map<std::string, int> * supportedKeys;
    std::map<std::string, int> Keybinds;
    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //resources
    std::map<std::string, sf::Texture> textures;
    //functions
    virtual void initKeybinds() = 0;

public:
    State(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys, std::stack<State*> * states);
    virtual ~State();

    const bool& getQuit() const;
    void endState();
    
    virtual void updateMousePositions();
    virtual void updateInput(const float & dt) = 0;
    virtual void update(const float & dt) = 0;
    
    virtual void render(sf::RenderTarget * target = NULL) = 0;
};


#endif //STATE_H
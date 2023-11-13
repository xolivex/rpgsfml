#ifndef State_hpp
#define State_hpp
#include <SFML/Graphics.hpp>
#include <vector>


class State{
private:

protected:
    sf::RenderWindow * window;
    std::map<std::string, int> * supportedKeys;
    std::map<std::string, int> Keybinds;
    bool quit;
    //resources
    std::vector<sf::Texture> * textures;
    //functions
    virtual void initKeybinds() = 0;

public:
    State(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys);
    virtual ~State();

    const bool& getQuit() const;

    virtual void checkForQuit();
    virtual void endState() = 0;
    virtual void updateInput(const float & dt) = 0;
    virtual void update(const float & dt) = 0;
    
    virtual void render(sf::RenderTarget * target = NULL) = 0;
};


#endif
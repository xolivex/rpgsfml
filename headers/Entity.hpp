#ifndef Entity_hpp
#define Entity_hpp

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>

class Entity
{
private:
protected:
    sf::RectangleShape shape;
    float movementSpeed;
public:
    Entity();
    virtual ~Entity();
    //functions
    virtual void move(const float & dt, const float dir_x, const float dir_y);

    virtual void update(const float & dt);
    virtual void render(sf::RenderTarget * target);
};

#endif
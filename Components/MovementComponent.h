#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "../includes.h"

enum movement_state {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent
{
private:
    sf::Sprite& sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

    //Initializer Functios

public:
    MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceletaion, float deceleration);
    virtual ~MovementComponent();

    //Acessors
    const float& getMaxVelocity() const;
    const sf::Vector2f getVelocity();
    //Functions
    const bool getState(const unsigned short state) const;
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();
    

    void move(const float x, const float y,const float& dt);
    void update(const float& dt);
};





#endif //MOVEMENT_COMPONENT_H
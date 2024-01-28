#include "MovementComponent.h"


//Constructors and Destructors
MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, 
float acceleration, float deceleration)
: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)

{
    
}

MovementComponent::~MovementComponent()
{
}
//Acessors
const float&  MovementComponent::getMaxVelocity() const
{
    return this->maxVelocity;
}

// Functions
const sf::Vector2f MovementComponent::getVelocity()
{
    return this->velocity;
}

const bool MovementComponent::getState(const unsigned short state) const
{
    switch (state)
    {
    case IDLE:
        if(this->velocity.x == 0.f && this->velocity.y == 0.f)
            return true;
        return false;
        break;
    case MOVING:
        if(this->velocity.x != 0.f || this->velocity.y != 0.f)
            return true;
        return false;
        break;
    case MOVING_LEFT:
        if(this->velocity.x < 0.f)
            return true;
        return false;
        break;
    case MOVING_RIGHT:
        if(this->velocity.x > 0.f)
            return true;
        return false;
        break;
    case MOVING_UP:
        if(this->velocity.y < 0.f)
            return true;
        return false;
        break;
    case MOVING_DOWN:
        if(this->velocity.y > 0.f)
            return true;
        return false;
        break;
    default:
        break;
    }
}

void MovementComponent::stopVelocity()
{
    this->velocity.x = 0.f;
    this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
    this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
    this->velocity.y = 0.f;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt)
{
   
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;
    
}

void MovementComponent::update(const float &dt)
{
    //acceleration
    //x positive
    if(this->velocity.x > 0.f)
    {
        if(this->velocity.x > this->maxVelocity)
            this->velocity.x = this->maxVelocity;
    }else if(this->velocity.x < 0.f)
    {
        if(this->velocity.x < -this->maxVelocity)
            this->velocity.x = -this->maxVelocity;
    }
    //y positive
    if(this->velocity.y > 0.f)
    {
        if(this->velocity.y > this->maxVelocity)
            this->velocity.y = this->maxVelocity;
    }else if(this->velocity.y < 0.f)
    {
        if(this->velocity.y < -this->maxVelocity)
            this->velocity.y = -this->maxVelocity;
    }
    //deceleration
    //x
    if(this->velocity.x > 0.f)
    {
        this->velocity.x -= deceleration;
        if(this->velocity.x < 0.f)
            this->velocity.x = 0.f;

    }else if(this->velocity.x < 0.f)
    {
        this->velocity.x += deceleration;
        if(this->velocity.x > 0.f)
            this->velocity.x = 0.f;
    }
    //y
    if(this->velocity.y > 0.f)
    {
        this->velocity.y -= deceleration;
        if(this->velocity.y < 0.f)
            this->velocity.y = 0.f;

    }else if(this->velocity.y < 0.f)
    {
        this->velocity.y += deceleration;
        if(this->velocity.y > 0.f)
            this->velocity.y = 0.f;
    }

    this->sprite.move(this->velocity * dt);
}

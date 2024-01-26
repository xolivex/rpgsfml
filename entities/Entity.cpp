#include "Entity.h"



void Entity::initVariables()
{
    this->movementComponent = NULL;
    this->animationComponent = NULL;
    this->hitboxComponent = NULL;
}


Entity::Entity()
{
    this->initVariables();
}

Entity::~Entity()
{
    delete this->movementComponent;
    delete this->animationComponent;
    delete this->hitboxComponent;
}

//Component functions
void Entity::setTexture(sf::Texture & texture)
{
    this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(float maxVelocity, const float acceleration, const float deceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}
void Entity::createAnimationComponent(sf::Texture &texture_sheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Sprite &sprite, 
    float offset_x, float offset_y,
    float width, float height)
{
    this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

const sf::Vector2f &Entity::getPosition() const
{
    if(this->hitboxComponent)
        return this->hitboxComponent->getPosition();
    
    return this->sprite.getPosition();
}

const sf::RectangleShape Entity::getShape() const
{
    return this->hitboxComponent->getShape();
}

// Functions

void Entity::setPosition(const float x, const float y)
{
    if(this->hitboxComponent)
        this->hitboxComponent->setPosition(x, y);
    else
        this->sprite.setPosition(x, y);
    
}

void Entity::move(const float dir_x, const float dir_y, const float &dt) 
{
    if(this->movementComponent)
    {
        this->movementComponent->move(dir_x, dir_y, dt); //set velocitys
    }
}

void Entity::update(const float &dt)
{
    if(this->movementComponent)
    {
        this->movementComponent->update(dt);
    }
}

void Entity::render(sf::RenderTarget & target)
{
    target.draw(this->sprite);

    if(this->hitboxComponent)
        this->hitboxComponent->render(target);
}
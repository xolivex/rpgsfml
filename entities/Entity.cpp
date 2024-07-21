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
    delete this->attributecomponent;
}

//Component functions
void Entity::setTexture(sf::Texture & texture)
{
    //ainda não ta sendo usado
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

void Entity::createAttributeComponent(const unsigned int level)
{
    this->attributecomponent = new AttributeComponent(level);
}

const sf::Vector2f &Entity::getPosition() const
{
    if(this->hitboxComponent)
        return this->hitboxComponent->getPosition();
    
    return this->sprite.getPosition();
}

const sf::Vector2i Entity::getGridPosition(int gridSizeI)
{
    if(this->hitboxComponent)
    {
        return sf::Vector2i(
            static_cast<int>(
                this->hitboxComponent->getPosition().x + this->hitboxComponent->getGlobalBounds().width / 2.f) / gridSizeI,
            static_cast<int>(
                this->hitboxComponent->getPosition().y + this->hitboxComponent->getGlobalBounds().height / 2.f) / gridSizeI
        );
    }
    
    return sf::Vector2i(
        static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
        static_cast<int>(this->sprite.getPosition().y) / gridSizeI
    );
}

const sf::FloatRect Entity::getGlobalBounds() const
{
    return this->hitboxComponent->getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float & dt) const
{
    if(this->hitboxComponent && this->movementComponent)
    {
        
        return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
    }
    
    return sf::FloatRect(-1.f,-1.f,-1.f,-1.f);
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

void Entity::stopVelocity()
{
    this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
    this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
    this->movementComponent->stopVelocityY();
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
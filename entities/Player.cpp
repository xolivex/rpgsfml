#include "Player.h"

//Variables


//Initializer functions
void Player::initVariables()
{
    this->attacking = false;
}

void Player::initComponent()
{
    
}

//Constructors and Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet) 
{
    this->initVariables();
    this->initComponent();
    this->setPosition(x, y);

    this->createHitboxComponent(this->sprite, 86.f, 81.f, 86.f, 111.f);
    this->createMovementComponent(300.f, 30.f, 10.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 13, 0, 192, 192);
    this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 11, 1, 192, 192);
    this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192*2, 192);

}

Player::~Player()
{
    
}

//Functions
void Player::update(const float &dt)
{
    this->movementComponent->update(dt);
    bool not_priority = false;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
       this->attacking = true;
    }
    if(this->attacking)
    {
        if(this->animationComponent->play("ATTACK", dt, true))
            this->attacking = false;
            
    }
    if(this->movementComponent->getState(IDLE))
    {
        this->animationComponent->play("IDLE", dt, not_priority);
    }
    else if(this->movementComponent->getState(MOVING_LEFT))
    {
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity(), not_priority);
    }else if(this->movementComponent->getState(MOVING_RIGHT))
    {
        this->sprite.setOrigin(258.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity(), not_priority);
    }
    else if(this->movementComponent->getState(MOVING_UP))
    {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(), not_priority);
    }
    else if(this->movementComponent->getState(MOVING_DOWN))
    {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(), not_priority);
    }
    

    this->hitboxComponent->update();
}
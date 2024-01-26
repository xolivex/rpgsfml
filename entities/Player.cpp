#include "Player.h"

// Variables

// Initializer functions
void Player::initVariables()
{
    this->attacking = false;
}

void Player::initComponent()
{
}

// Constructors and Destructors
Player::Player(float x, float y, sf::Texture &texture_sheet)
{
    this->initVariables();
    this->initComponent();
    this->setPosition(x, y);

    this->createHitboxComponent(this->sprite, 86.f, 81.f, 86.f, 111.f);
    this->createMovementComponent(500.f, 50.f, 15.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 13, 0, 192, 192);
    this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 11, 1, 192, 192);
    this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192 * 2, 192);
}

Player::~Player()
{
}

void Player::updateAttack()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        this->attacking = true;
    }
}

void Player::updateAnimation(const float &dt)
{
    if (this->attacking)
    {
        if (this->sprite.getScale().x > 0.f) // FACING LEFT
        {
            this->sprite.setOrigin(96.f, 0.f);
        }
        else // FACING RIGHT
        {
            this->sprite.setOrigin(258.f + 96.F, 0.f);
        }

        if (this->animationComponent->play("ATTACK", dt, true))
        {
            if (this->sprite.getScale().x > 0.f) // FACING LEFT
            {
                this->sprite.setOrigin(0.f, 0.f);
            }
            else // FACING RIGHT
            {
                this->sprite.setOrigin(258.f, 0.f);
            }
            this->attacking = false;
        }
    }
    if (this->movementComponent->getState(IDLE))
    {
        this->animationComponent->play("IDLE", dt, false);
    }
    else if (this->movementComponent->getState(MOVING_LEFT))
    {
        if (this->sprite.getScale().x < 0.f)
        {
            this->sprite.setOrigin(0.f, 0.f);
            this->sprite.setScale(1.f, 1.f);
        }
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity(), false);
    }
    else if (this->movementComponent->getState(MOVING_RIGHT))
    {
        if (this->sprite.getScale().x > 0.f)
        {
            this->sprite.setOrigin(258.f, 0.f);
            this->sprite.setScale(-1.f, 1.f);
        }
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity(), false);
    }
    else if (this->movementComponent->getState(MOVING_UP))
    {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(), false);
    }
    else if (this->movementComponent->getState(MOVING_DOWN))
    {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(), false);
    }
}

// Functions
void Player::update(const float &dt)
{
    this->movementComponent->update(dt);
    this->updateAttack();
    this->updateAnimation(dt);
    this->hitboxComponent->update();
}

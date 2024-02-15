#ifndef ENTITY_H
#define ENTITY_H

#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/HitboxComponent.h"

class Entity
{
private:
    void initVariables();
protected:
    sf::Sprite sprite;
    sf::FloatRect defaultFR;
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;
    HitboxComponent* hitboxComponent;
public:
    Entity();
    virtual ~Entity();
    //Component functions
    void setTexture(sf::Texture& texture);
    void createMovementComponent(float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture& texture_sheet);
    void createHitboxComponent(sf::Sprite& sprite, 
        float offset_x, float offset_y,
        float width, float height);
    //Accessors
    virtual const sf::Vector2f& getPosition() const;
    virtual const sf::Vector2i getGridPosition(int gridSizeI);
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::FloatRect & getNextPositionBounds(const float & dt) const;
    //Modiffiers
    virtual void setPosition(const float x, const float y);

    //functions
    virtual void move(const float dir_x, const float dir_y, const float &dt);
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    virtual void update(const float & dt);
    virtual void render(sf::RenderTarget & target);
};

#endif //ENTITY_H
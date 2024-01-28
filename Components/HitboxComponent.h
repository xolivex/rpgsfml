#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include "../includes.h"


class HitboxComponent
{
private:
    sf::RectangleShape hitbox;
    sf::Sprite& sprite;

    float offsetX;
    float offsetY;
public:
    HitboxComponent(sf::Sprite& sprite,
    float offset_x, float offset_y,
    float width, float height);
    virtual ~HitboxComponent();
    //Accessors
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect& getGlobalBounds() const;

    //Modifiers
    void setPosition(const sf::Vector2f position);
    void setPosition(const float x, const float y);

    //Functions
    bool checkIntersec(const sf::FloatRect& frect);

    void update();
    void render(sf::RenderTarget& target);
};

#endif //HITBOXCOMPONENT_H
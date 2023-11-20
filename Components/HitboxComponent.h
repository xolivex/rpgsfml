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

    //Functions
    bool checkIntersec(const sf::FloatRect& frect);

    void update();
    void render(sf::RenderTarget& target);
};

#endif //HITBOXCOMPONENT_H
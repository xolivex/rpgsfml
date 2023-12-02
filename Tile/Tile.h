#ifndef TILE_H
#define TILE_H

#include "../includes.h"

class Tile
{
private:

protected:
    sf::RectangleShape shape;
public:
    Tile();
    Tile(float x, float y, float gridSizeF, sf::Texture& texture, const sf::IntRect& textureRect);
    virtual ~Tile();

    //Functions
    void update();
    void render(sf::RenderTarget & target);
};

#endif //TILE_H
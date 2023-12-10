#ifndef TILE_H
#define TILE_H

#include "../includes.h"

enum Typetile { DEFAULT = 0};

class Tile
{
private:

protected:
    sf::RectangleShape shape;
    bool collision;
    short type;
public:
    Tile();
    Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, sf::Texture& texture, const sf::IntRect& textureRect,
    bool collision = false, short type = Typetile::DEFAULT);
    virtual ~Tile();
    //Accessors
    const std::string getAsString() const;
    

    //Functions
    void update();
    void render(sf::RenderTarget & target);
};

#endif //TILE_H
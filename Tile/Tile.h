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
    Tile(int grid_x, int grid_y, float gridSizeF, sf::Texture& texture, const sf::IntRect& textureRect,
    bool collision = false, int type = Typetile::DEFAULT);
    virtual ~Tile();
    //Accessors
    const bool getCollision() const;
    const sf::FloatRect getGlobalBounds() const;
    const sf::Vector2f& getPosition() const;
    const bool intersect(sf::FloatRect frect) const;
    const std::string getAsString() const;
    

    //Functions
    void update();
    void render(sf::RenderTarget & target);
};

#endif //TILE_H
#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

class TileMap
{
private:
    float gridSizeF;
    unsigned gridSizeU;
    sf::Vector2u maxSize;
    unsigned layers;
    std::vector< std::vector< std::vector< Tile *> > > map;
    sf::Texture tileTextureSheet;

public:
    TileMap(float grid_SizeF, float width, float height);
    virtual ~TileMap();

    //Functions
    void update();
    void render(sf::RenderTarget & target);

    void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);
    
};

#endif //TILEMAP_H
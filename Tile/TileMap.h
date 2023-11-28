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

public:
    TileMap(float grid_SizeF, float width, float height);
    virtual ~TileMap();

    //Functions
    void update();
    void render(sf::RenderTarget & target);

    void addTile();
    void removeTile();
    
};

#endif //TILEMAP_H
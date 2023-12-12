#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

class TileMap
{
private:
    float gridSizeF;
    unsigned gridSizeU;
    unsigned layers;
    std::string textureFile;
    sf::Vector2u maxSize;
    std::vector< std::vector< std::vector< Tile *> > > map;
    sf::Texture tileTextureSheet;

    void clear();
public:
    TileMap(float grid_SizeF, float width, float height, std::string texture_file);
    virtual ~TileMap();


    //Accessors
    const sf::Texture* getTileSheet() const;

    //Functions
    void update();
    void render(sf::RenderTarget & target);

    void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect, const bool collision, const short type);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);

    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);
};

#endif //TILEMAP_H
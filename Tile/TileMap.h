#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "../entities/Entity.h"

class Entity;

class TileMap
{
private:
    float gridSizeF;
    unsigned gridSizeU;
    unsigned layers;
    std::string textureFile;
    sf::Vector2u maxSizeWorldGrid;
    sf::Vector2f maxSizeWorldF;
    std::vector< std::vector< std::vector< Tile *> > > map;
    sf::Texture tileTextureSheet;
    sf::RectangleShape collisionBox;
    int fromX;
    int fromY;
    int toX;
    int toY;
    int maxCullingX = 3;
    int maxCullingY = 3;

    void clear();
public:
    TileMap(float grid_SizeF, float width, float height, std::string texture_file);
    virtual ~TileMap();


    //Accessors
    const sf::Texture* getTileSheet() const;

    //Functions
    void update();
    void updateCollision(Entity * entity, const float & dt);
    void render(sf::RenderTarget & target);

    void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect, const bool collision, const short type);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);

    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);
};

#endif //TILEMAP_H
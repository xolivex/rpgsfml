#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "../entities/Entity.h"

class Entity;

class TileMap
{
private:
    float gridSizeF;
    int gridSizeI;
    int layers;
    enum renderTypegame
    {
        RENDER_GAME = 0,
        RENDER_EDITOR
    };
    int renderType;
    std::string textureFile;
    sf::Vector2i maxSizeWorldGrid;
    sf::Vector2f maxSizeWorldF;
    std::vector< std::vector< std::vector< std::vector< Tile *> > > > map;
    sf::Texture tileTextureSheet;
    sf::RectangleShape collisionBox;
    int fromX;
    int fromY;
    int toX;
    int toY;
    int maxCullingX = 1;
    int maxCullingY = 1;
    int maxRenderCullingX = 10;
    int maxRenderCullingY = 6;

    void clear();
public:
    TileMap(float grid_SizeF, float width, float height, std::string texture_file, int render_type = renderTypegame::RENDER_GAME);
    virtual ~TileMap();


    //Accessors
    const sf::Texture* getTileSheet() const;

    //Functions
    void update();
    void updateCollision(Entity * entity, const float & dt);
    void render(sf::RenderTarget & target);

    void addTile(const int x, const int y, const int layer, const sf::IntRect& textureRect, const bool collision, const int type);
    void removeTile(const int x, const int y, const int layer = 0);

    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);
};

#endif //TILEMAP_H
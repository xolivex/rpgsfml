#include "TileMap.h"

TileMap::TileMap(float grid_SizeF, float width, float height)
{
    this->gridSizeF = grid_SizeF;
    this->gridSizeU = static_cast<unsigned>(gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;

    this->layers = 1;
    this->map.resize(this->maxSize.x);
    for(size_t x = 0; x < this->maxSize.x ; x++)
    {
        this->map.push_back(std::vector< std::vector<Tile*> > ());
        for(size_t y = 0;y < this->maxSize.y ; y++)
        {
            this->map[x].resize(this->maxSize.y);
            this->map[x].push_back(std::vector<Tile*> ());
            for(size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].resize(this->layers);
                this->map[x][y].push_back(nullptr);
            }
        }
    }
}

TileMap::~TileMap()
{
}

//Functions

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget &target)
{
    for(auto &x : this->map)
    {
        for(auto &y : x)
        {
            for(auto &z : y)
            {
                if(z)
                    z->render(target);
            }
        }
    }
}

void TileMap::addTile()
{
}

void TileMap::removeTile()
{
}

#include "TileMap.h"

TileMap::TileMap(float grid_SizeF, float width, float height)
{
    this->gridSizeF = grid_SizeF;
    this->gridSizeU = static_cast<unsigned>(gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;

    this->layers = 1;
    this->map.resize(this->maxSize.x, std::vector< std::vector<Tile*> > ());
    for(size_t x = 0; x < this->maxSize.x ; x++)
    {
        for(size_t y = 0;y < this->maxSize.y ; y++)
        {
            this->map[x].resize(this->maxSize.y, std::vector<Tile*> ());
            for(size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].resize(this->layers, NULL);
            }
        }
    }

    if(!this->tileTextureSheet.loadFromFile("Resources/image/tile/tilesheet1.png"))
        std::cout << "ERROR::TILEMAP::NOT_LOAD::TEXTURE_TILE"<< "\n";
}

TileMap::~TileMap()
{
    for(size_t x = 0; x < this->maxSize.x ; x++)
    {
        for(size_t y = 0;y < this->maxSize.y ; y++)
        {
            for(size_t z = 0; z < this->layers; z++)
            {
                delete map[x][y][z];
            }
        }
    }
}


//Functions

const sf::Texture*  TileMap::getTileSheet() const
{
    return &this->tileTextureSheet;
}

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

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect)
{
    /**/
    if(x < this->maxSize.x && x >= 0
     && y < this->maxSize.y && y >= 0
     && z < this->layers && z >= 0)
    {
        if(this->map[x][y][z] == NULL)
        {
            this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileTextureSheet, textureRect);
            std::cout << "DEBUG: ADD 1 ONLY TIME!!" << "\n";
        }
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
    if(x < this->maxSize.x && x >= 0
     && y < this->maxSize.y && y >= 0
     && z < this->layers && z >= 0)
    {
        if(this->map[x][y][z] != NULL)
        {
            delete this->map[x][y][z];
            this->map[x][y][z] = NULL;
            std::cout << "DEBUG: REMOVE 1 ONLY TIME!!" << "\n";
        }
    }
}

void TileMap::loadFromFile(const std::string file_name)
{
}

void TileMap::saveToFile(const std::string file_name)
{
}

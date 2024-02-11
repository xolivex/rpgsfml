#include "TileMap.h"

void TileMap::clear()
{
    for(size_t x = 0; x < this->maxSizeWorldGrid.x ; x++)
    {
        for(size_t y = 0;y < this->maxSizeWorldGrid.y ; y++)
        {
            for(size_t z = 0; z < this->layers; z++)
            {
                delete map[x][y][z];
                this->map[x][y][z] = NULL;
            }
            
        }
        
    }
    this->map.clear();
    //std::cout << this->map.size() << "\n";
}

TileMap::TileMap(float grid_SizeF, float width, float height, std::string texture_file)
{
    this->gridSizeF = grid_SizeF;
    this->gridSizeU = static_cast<unsigned>(gridSizeF);
    this->maxSizeWorldGrid.x = width;
    this->maxSizeWorldGrid.y = height;
    this->maxSizeWorldF.x = width * grid_SizeF;
    this->maxSizeWorldF.y = height * grid_SizeF;
    this->textureFile = texture_file;

    this->layers = 1;
    this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<Tile*> > ());
    for(size_t x = 0; x < this->maxSizeWorldGrid.x ; x++)
    {
        for(size_t y = 0;y < this->maxSizeWorldGrid.y ; y++)
        {
            this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*> ());
            for(size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].resize(this->layers, NULL);
            }
        }
    }

    if(!this->tileTextureSheet.loadFromFile(this->textureFile))
        std::cout << "ERROR::TILEMAP::NOT_LOAD::TEXTURE_TILE_NAME:"<< this->textureFile <<"\n";

    this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
    this->collisionBox.setFillColor(sf::Color(255,0,0,50));
    this->collisionBox.setOutlineThickness(1.f);
    this->collisionBox.setOutlineColor(sf::Color::Red);
}

TileMap::~TileMap()
{
    this->clear();
}


//Functions

const sf::Texture*  TileMap::getTileSheet() const
{
    return &this->tileTextureSheet;
}

void TileMap::update()
{
}

void TileMap::updateCollision(Entity *entity)
{
    if(entity->getPosition().x < 0.f)
    {
        entity->setPosition(0.f,entity->getPosition().y);
        entity->stopVelocityX();
    }
    else if(entity->getPosition().x > this->maxSizeWorldF.x - entity->getGlobalBounds().width)
    {
        entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
        entity->stopVelocityX();
    }
    if(entity->getPosition().y < 0.f)
    {
        entity->setPosition(entity->getPosition().x, 0.f);
        entity->stopVelocityY();
    }
    else if(entity->getPosition().y > this->maxSizeWorldF.y - entity->getGlobalBounds().height)
    {
        entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
        entity->stopVelocityY();
    }
    //culling
    this->fromX = entity->getGridPosition(this->gridSizeU).x;
    this->fromX = this->fromX - this->maxCullingX;
    
    this->toX = entity->getGridPosition(this->gridSizeU).x;
    this->toX = this->toX + this->maxCullingX;

    if(this->fromX < 0)
        this->fromX = 0;
    else if(this->toX > this->maxSizeWorldGrid.x)
        this->toX = this->maxSizeWorldGrid.x;
    
    this->fromY = entity->getGridPosition(this->gridSizeU).y;
    this->fromY = this->fromY - this->maxCullingY;
    this->toY = entity->getGridPosition(this->gridSizeU).y;
    this->toY = this->toY + this->maxCullingY;

    if(this->fromY < 0)
        this->fromY = 0;
    else if(this->toY > this->maxSizeWorldGrid.y)
        this->toY = this->maxSizeWorldGrid.y;
    //collision culling

    for(int x = this->fromX; x < this->toX; x++)
    {
        for(int y = this->fromY ;y < this->toY ; y++)
        {
            for(int z = 0; z < this->layers; z++)
            {
                if(this->map[x][y][z]->getCollision() && this->map[x][y][z]->intersect(entity->getGlobalBounds()))
                {
                    std::cout << "COLISION!" << "\n";
                    
                }
                    
            }
            
        }
        
    }

}

void TileMap::render(sf::RenderTarget &target)
{
    /*for(auto &x : this->map)
    {
        for(auto &y : x)
        {
            for(auto &z : y)
            {
                if(z)
                {
                    z->render(target);
                    if(z->getCollision())
                    {
    	                this->collisionBox.setPosition(z->getPosition());
                        target.draw(this->collisionBox);
                    }
                }
            }
        }
    }*/

    for(int x = this->fromX; x < this->toX; x++)
    {
        for(int y = this->fromY ;y < this->toY ; y++)
        {
            for(int z = 0; z < this->layers; z++)
            {
                if(this->map[x][y][z])
                    this->map[x][y][z]->render(target);
            }
            
        }
        
    }
}

void TileMap::addTile(const unsigned x, const unsigned y, 
const unsigned z, const sf::IntRect& textureRect, const bool collision, const short type)
{
    /**/
    if(x < this->maxSizeWorldGrid.x && x >= 0
     && y < this->maxSizeWorldGrid.y && y >= 0
     && z < this->layers && z >= 0)
    {
        if(this->map[x][y][z] == NULL)
        {
            this->map[x][y][z] = new Tile(x , y, this->gridSizeF, this->tileTextureSheet, textureRect, collision, type);
            std::cout << "DEBUG: ADD 1 ONLY TIME!!" << "\n";
        }
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
    if(x < this->maxSizeWorldGrid.x && x >= 0
     && y < this->maxSizeWorldGrid.y && y >= 0
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

    std::ifstream in_file;
    in_file.open(file_name);
    
    if(in_file.is_open())
    {
        
        sf::Vector2u size;
        unsigned gridSize = 0;
        unsigned layers = 0;
        std::string texturefile = "";
        unsigned x = 0;
        unsigned y = 0;
        unsigned z = 0;
        unsigned trLeft = 0;
        unsigned trTop = 0;
        bool collision = false;
        short type = 0;
       
        
        //Basics
        in_file >> size.x >> size.y >> gridSize >> layers >> texturefile;
        this->gridSizeF = static_cast<float>(gridSize);
        this->gridSizeU = gridSize;
        this->maxSizeWorldGrid.x = size.x;
        this->maxSizeWorldGrid.y = size.y;
        this->layers = layers;
        this->textureFile = texturefile;

        this->clear();

        this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<Tile*> > ());
        for(size_t x = 0; x < this->maxSizeWorldGrid.x ; x++)
        {
            for(size_t y = 0;y < this->maxSizeWorldGrid.y ; y++)
            {
                this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*> ());
                for(size_t z = 0; z < this->layers; z++)
                {
                    this->map[x][y].resize(this->layers, NULL);
                }
            }
        }
    	
        if(!this->tileTextureSheet.loadFromFile(texturefile))
        std::cout << "ERROR::TILEMAP::NOT_LOAD::TEXTURE_TILE_NAME:"<< texturefile <<"\n";
        
        while(in_file >> x >> y >> z >> trLeft >> trTop >> collision >> type)
        {            
            this->map[x][y][z] = new Tile(x , y, 
            this->gridSizeF, this->tileTextureSheet, 
            sf::IntRect(trLeft , trTop, this->gridSizeU, this->gridSizeU), 
            collision, type);
        }
        
    }
    else
    {
        std::cout << "ERRO::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name <<"\n";
    }
}

void TileMap::saveToFile(const std::string file_name)
{
    std::ofstream out_file;
    out_file.open(file_name);
    if(out_file.is_open())
    {
        out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y <<"\n"
        << this->gridSizeU <<"\n"
        << this->layers << "\n"
        << this->textureFile <<"\n";

        for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
        {
            for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
            {
                for (size_t z = 0; z < this->layers; z++)
                {
                    if(this->map[x][y][z])
                        out_file  << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString();
                }
            }
        }
    }
    else
    {
        std::cout << "ERRO::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name <<"\n";
    }

    out_file.close();
}

#include "TileMap.h"

void TileMap::clear()
{
    for(int x = 0; x < this->maxSizeWorldGrid.x ; x++)
    {
        for(int y = 0;y < this->maxSizeWorldGrid.y ; y++)
        {
            for(int layer = 0; layer < this->layers; layer++)
            {
                for(int k = 0; k < map[x][y][layer].size(); k++)
                {
                    delete this->map[x][y][layer][k];
                    this->map[x][y][layer].pop_back();
                }
            }
            
        }
        
    }
    this->map.clear();
    //std::cout << this->map.size() << "\n";
}

TileMap::TileMap(float grid_SizeF, float width, float height, std::string texture_file, int render_type)
{
    this->fromX = 0;
    this->fromY = 0;
    this->toX = 0;
    this->toY = 0;
    this->gridSizeF = grid_SizeF;
    this->gridSizeI = static_cast<int>(gridSizeF);
    this->maxSizeWorldGrid.x = static_cast<int>(width);
    this->maxSizeWorldGrid.y = static_cast<int>(height);
    this->maxSizeWorldF.x = width * grid_SizeF;
    this->maxSizeWorldF.y = height * grid_SizeF;
    this->textureFile = texture_file;
    this->renderType = render_type;
    this->layers = 1;
    this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > > ());
    for(int x = 0; x < this->maxSizeWorldGrid.x ; x++)
    {
        this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> > ());
        for(int y = 0;y < this->maxSizeWorldGrid.y ; y++)
        {
            this->map[x][y].resize(this->layers, std::vector<Tile*>());
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

void TileMap::updateCollision(Entity *entity, const float & dt)
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
    this->fromX = entity->getGridPosition(this->gridSizeI).x;
    this->fromX -= this->maxCullingX;
    
    this->toX = entity->getGridPosition(this->gridSizeI).x;
    this->toX += this->maxCullingX + 1;

    //prevents negative number in vector map x
   if(this->fromX < 0)
        this->fromX = 0;
    else if(this->toX > this->maxSizeWorldGrid.x)
        this->toX = this->maxSizeWorldGrid.x;
    
    this->fromY = entity->getGridPosition(this->gridSizeI).y;
    this->fromY -= this->maxCullingY;
    this->toY = entity->getGridPosition(this->gridSizeI).y;
    this->toY += this->maxCullingY + 1;

    //prevents negative number in vector map y
    if(this->fromY < 0)
        this->fromY = 0;
    else if(this->toY > this->maxSizeWorldGrid.y)
        this->toY = this->maxSizeWorldGrid.y;
    
    //collision culling

    for(int x = this->fromX; x < this->toX; x++)
    {
        for(int y = this->fromY ;y < this->toY ; y++)
        {
            for(int layer = 0; layer < this->layers; layer++)
            {
                for(int k = 0; k < this->map[x][y][layer].size(); k++)
                {
                    if (this->map[x][y][layer][k])
                    {

                        sf::FloatRect playerbounds = entity->getGlobalBounds();
                        sf::FloatRect wallbounds = this->map[x][y][layer][k]->getGlobalBounds();
                        sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
                        std::cout << nextPositionBounds.left << " - " << nextPositionBounds.top << "\n";

                        if (this->map[x][y][layer][k]->getCollision() &&
                            this->map[x][y][layer][k]->intersect(nextPositionBounds)

                        )
                        {
                            std::cout << "COLISION!"
                                      << "\n";
                            // botton collision
                            if (playerbounds.top < wallbounds.top && playerbounds.top + playerbounds.height < wallbounds.top + wallbounds.height && playerbounds.left < wallbounds.left + wallbounds.width && playerbounds.left + playerbounds.width > wallbounds.left)
                            {
                                entity->stopVelocityY();
                                entity->setPosition(playerbounds.left, wallbounds.top - playerbounds.height);
                            }
                            // top collision
                            else if (playerbounds.top > wallbounds.top && playerbounds.top + playerbounds.height > wallbounds.top + wallbounds.height && playerbounds.left < wallbounds.left + wallbounds.width && playerbounds.left + playerbounds.width > wallbounds.left)
                            {
                                entity->stopVelocityY();
                                entity->setPosition(playerbounds.left, wallbounds.top + wallbounds.height);
                            }

                            // right collision
                            if (playerbounds.left < wallbounds.left && playerbounds.left + playerbounds.width < wallbounds.left + wallbounds.width && playerbounds.top < wallbounds.top + wallbounds.height && playerbounds.top + playerbounds.height > wallbounds.top

                            )
                            {
                                entity->stopVelocityX();
                                entity->setPosition(wallbounds.left - playerbounds.width, playerbounds.top);
                            }
                            // left collision
                            else if (playerbounds.left > wallbounds.left && playerbounds.left + playerbounds.width > wallbounds.left + wallbounds.width && playerbounds.top < wallbounds.top + wallbounds.height && playerbounds.top + playerbounds.height > wallbounds.top

                            )
                            {
                                entity->stopVelocityX();
                                entity->setPosition(wallbounds.left + wallbounds.width, playerbounds.top);
                            }
                        }
                    }
                }
            }
            
        }
        
    }
    //culling render
    this->fromX = entity->getGridPosition(this->gridSizeI).x;
    this->fromX -= this->maxRenderCullingX;
    
    this->toX = entity->getGridPosition(this->gridSizeI).x;
    this->toX += this->maxRenderCullingX + 1;

    //prevents negative number in vector map x
   if(this->fromX < 0)
        this->fromX = 0;
    else if(this->toX > this->maxSizeWorldGrid.x)
        this->toX = this->maxSizeWorldGrid.x;
    
    this->fromY = entity->getGridPosition(this->gridSizeI).y;
    this->fromY -= this->maxRenderCullingY;
    this->toY = entity->getGridPosition(this->gridSizeI).y;
    this->toY += this->maxRenderCullingY + 1;

    //prevents negative number in vector map y
    if(this->fromY < 0)
        this->fromY = 0;
    else if(this->toY > this->maxSizeWorldGrid.y)
        this->toY = this->maxSizeWorldGrid.y;
}

void TileMap::render(sf::RenderTarget &target)
{
    if(renderType == renderTypegame::RENDER_EDITOR)
    {

        for (auto &x : this->map)
        {
            for (auto &y : x)
            {
                for (auto &z : y)
                {
                    for (auto *k : z)
                    {
                        if (k)
                        {
                            k->render(target);
                            if (k->getCollision())
                            {
                                this->collisionBox.setPosition(k->getPosition());
                                target.draw(this->collisionBox);
                            }
                        }
                    }
                }
            }
        }
    }
    
    if(renderType == renderTypegame::RENDER_GAME)
    {
        for (int x = this->fromX; x < this->toX; x++)
        {
            for (int y = this->fromY; y < this->toY; y++)
            {
                for (int z = 0; z < this->layers; z++)
                {
                    for (int k = 0; k < this->map[x][y][z].size(); k++)
                    {
                        if (this->map[x][y][z][k])
                            this->map[x][y][z][k]->render(target);
                    }
                }
            }
        }
    }
}

void TileMap::addTile(const int x, const int y, 
const int layer, const sf::IntRect& textureRect, const bool collision, const int type)
{
    
    if(x < this->maxSizeWorldGrid.x && x >= 0
     && y < this->maxSizeWorldGrid.y && y >= 0
     && layer < this->layers && layer >= 0)
    {
            this->map[x][y][layer].push_back(new Tile(x , y, this->gridSizeF, this->tileTextureSheet, textureRect, collision, type));
            std::cout << "DEBUG: ADD 1 ONLY TIME!!" << "\n";
    }
}

void TileMap::removeTile(const int x, const int y, const int layer)
{
    if(x < this->maxSizeWorldGrid.x && x >= 0
     && y < this->maxSizeWorldGrid.y && y >= 0
     && layer < this->layers && layer >= 0)
    {
        if(!this->map[x][y][layer].empty())
        {
            delete this->map[x][y][layer][this->map[x][y][layer].size() - 1];
            this->map[x][y][layer].pop_back();
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
        int  gridSize = 0;
        int layers = 0;
        std::string texturefile = "";
        int x = 0;
        int y = 0;
        int z = 0;
        int trLeft = 0;
        int trTop = 0;
        bool collision = false;
        int type = 0;
       
        
        //Basics
        in_file >> size.x >> size.y >> gridSize >> layers >> texturefile;
        this->gridSizeF = static_cast<float>(gridSize);
        this->gridSizeI = gridSize;
        this->maxSizeWorldGrid.x = size.x;
        this->maxSizeWorldGrid.y = size.y;
        this->layers = layers;
        this->textureFile = texturefile;

        this->clear();

        this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > > ());
        for(int x = 0; x < this->maxSizeWorldGrid.x ; x++)
        {
            this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> > ());
            for(int y = 0;y < this->maxSizeWorldGrid.y ; y++)
            {
                for(int z = 0; z < this->layers; z++)
                {
                    this->map[x][y].resize(this->layers, std::vector<Tile*>());
                }
            }
        }
    	
        if(!this->tileTextureSheet.loadFromFile(texturefile))
        std::cout << "ERROR::TILEMAP::NOT_LOAD::TEXTURE_TILE_NAME:"<< texturefile <<"\n";
        
        while(in_file >> x >> y >> z >> trLeft >> trTop >> collision >> type)
        {            
            //mudar valor de z depois
            this->map[x][y][z].push_back(new Tile(x , y, 
            this->gridSizeF, this->tileTextureSheet, 
            sf::IntRect(trLeft , trTop, this->gridSizeI, this->gridSizeI), 
            collision, type));
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
        << this->gridSizeI <<"\n"
        << this->layers << "\n"
        << this->textureFile <<"\n";

        for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
        {
            for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
            {
                for (int layer = 0; layer < this->layers; layer++)
                {
                    for (int k = 0; k < this->map[x][y][layer].size(); k++)
                    {
                        if(!this->map[x][y][layer].empty())
                            out_file  << x << " " << y << " " << layer << " " 
                            << this->map[x][y][layer][k]->getAsString();
                    }
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

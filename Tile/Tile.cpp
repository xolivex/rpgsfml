#include "Tile.h"

Tile::Tile()
{
    this->collision = false;
    this->type = 0;
}

Tile::Tile(int grid_x, int grid_y, float gridSizeF, sf::Texture& texture, const sf::IntRect& textureRect,
bool collision, int type)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF,static_cast<float>(grid_y) * gridSizeF);
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(textureRect);
    this->collision = collision;
    this->type = type;
}

Tile::~Tile()
{
}

const short Tile::getTileType()
{
    return this->type;
}

const bool Tile::getCollision() const
{
    return this->collision;
}

const sf::FloatRect Tile::getGlobalBounds() const
{
    return this->shape.getGlobalBounds();
}

const sf::Vector2f &Tile::getPosition() const
{
    return this->shape.getPosition();
}

const bool Tile::intersect(sf::FloatRect frect) const
{
    return this->shape.getGlobalBounds().intersects(frect);
}

const std::string Tile::getAsString() const
{
    std::stringstream ss;

    ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top 
    << " " << this->collision << " " << this->type << " ";

    return ss.str();
}


//Functions

void Tile::update()
{
}

void Tile::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
}

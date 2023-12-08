#include "Tile.h"

Tile::Tile()
{
    this->collision = false;
    this->type = 0;
}

Tile::Tile(float x, float y, float gridSizeF, sf::Texture& texture, const sf::IntRect& textureRect,
bool collision, short type)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setPosition(x, y);
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(textureRect);
    this->collision = false;
    this->type = 0;
}

Tile::~Tile()
{
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

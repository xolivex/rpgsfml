#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF, sf::Texture& texture, const sf::IntRect& textureRect)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setPosition(x, y);
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(textureRect);
}

Tile::~Tile()
{
}

//Functions

void Tile::update()
{
}

void Tile::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
}

#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned int level)
{
    this->level = level;
    this->exp = 0;
    //caculates next level experience
    this->expNext = static_cast<unsigned int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
    this->attributesPoints = 3;
    this->strength = 0;
    this->vitality = 0;
    this->dexterity = 0;
    this->accuracy = 0;
    this->agility = 0;
    this->defence = 0;
    this->intelligence = 0;
}

AttributeComponent::~AttributeComponent()
{
}

std::string AttributeComponent::debugPrint() const
{
    std::stringstream ss;
    ss << "Level: " << this->level << "\n"
        << "Exp: " << this->exp << "\n"
        << "Exp Next: " << this->expNext << "\n"
        << "Attripoint: " << this->attributesPoints << "\n";

    return ss.str();
}

void AttributeComponent::expGain(const unsigned exp)
{
    this->exp += exp;
    this->update_level();
}

void AttributeComponent::update_stats(const bool reset)
{
    this->hp_max = this->vitality * 9 + this->vitality + this->strength;
    this->damage_max = this->strength * 2 + this->strength / 2;
    this->damage_min = this->strength * 2 + this->strength / 4;
    this->accuracy = this->dexterity * 5 + this->dexterity / 2;
    this->defence = this->agility * 2 + this->agility / 4;
    this->luck = this->intelligence * 2 + this->intelligence / 5;

    if(reset)
    {
        this->hp = this->hp_max;
    }

}

void AttributeComponent::update_level()
{
    while(this->exp > this->expNext)
    {
        ++this->level;
        this->expNext = static_cast<unsigned int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
        ++this->attributesPoints;
    }
}

void AttributeComponent::update()
{
    this->update_stats(false);
    this->update_level();
}

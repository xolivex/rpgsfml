#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

#include "../includes.h"

class AttributeComponent
{
public:
    //Leveling
    unsigned int level;
    unsigned int exp;
    unsigned int expNext;
    unsigned int attributesPoints;

    //Attributes
    int strength;
    int vitality;
    int dexterity;
    int agility;
    int intelligence;

    //Stats
    int hp;
    int hp_max;
    int damage_min;
    int damage_max;
    int accuracy;
    int defence;
    int luck;

    AttributeComponent(unsigned int level);
    virtual ~AttributeComponent();
    std::string debugPrint() const;
    //insersors
    void expGain(const unsigned exp);

    void update_stats(const bool reset);
    void update_level();
    void update();
};


#endif
#ifndef PLEYER_H
#define PLAYER_H

#include "Entity.h"

class Entity;

class Player : public Entity
{
private:
    //Variables
    bool attacking;
    //Initializer functions
    void initVariables();
    void initComponent();
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Functions
    void updateAttack();
    void updateAnimation(const float& dt);
    virtual void update(const float& dt);

};


#endif //PLAYER_H
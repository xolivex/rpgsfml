#ifndef PlayerGUI_h
#define PlayerGUI_h

#include "../entities/Player.h"

class Player;

class PlayerGUI
{
private:
    Player * player;
    sf::Font font;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInner;
    void initFont();
    void initHpBar();

public:
    PlayerGUI(Player * player);
    ~PlayerGUI();

    void updateHpBar();
    void renderHpBar(sf::RenderTarget & target);
    void update(const float & dt);
    void render(sf::RenderTarget & target);
};



#endif //PlayerGUI_h
#include "GameState.h"

//Initializer functions
void GameState::initKeybinds()
{
    std::ifstream ifs("Config/gamestate_keybinds.ini");

    if(ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while(ifs >> key >> key2)
        {
            this->Keybinds[key] = this->supportedKeys->at(key2);
        }
       
    }

    ifs.close();

}
void GameState::initTextures()
{
    if(!this->textures["PLAYER_SHEET"].loadFromFile("Resources/image/sprites/player/PLAYER_SHEET.png"))
    {
        throw "ERROR::GAME_SATATE::COUD_NOT_LOAD_PLAYER_TEXTURE";
    }
}

void GameState::initPlayers()
{
    this->player = new Player(200.f,200.f,this->textures["PLAYER_SHEET"]);
}

//Constructors and Destructors
GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
}
GameState::~GameState()
{
    delete this->player;
}



void GameState::updateInput(const float &dt)
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_LEFT"))))
    {
        this->player->move(-1.f, 0.f, dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_RIGHT"))))
    {
        this->player->move(1.f, 0.f, dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_UP"))))
    {
        this->player->move(0.f, -1.f, dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_DOWN"))))
    {
        this->player->move(0.f, 1.f, dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("CLOSE"))))
    {
        this->endState();
    }
}


void GameState::update(const float & dt)
{
    this->updateMousePositions();
    this->updateInput(dt);

    this->player->update(dt);
}

void GameState::render(sf::RenderTarget * target)
{
    if(!target)
    {
        target = this->window;
    }
    this->player->render(*target);
}

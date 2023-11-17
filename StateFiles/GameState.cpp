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

void GameState::initPausedMenu()
{
    pmenu = new PausedMenu(*this->window,this->font);
}

void GameState::initFonts()
{
    if(!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
    }
}

//Constructors and Destructors
GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
    this->initFonts();
    this->initPausedMenu();  
}
GameState::~GameState()
{
    delete pmenu;
    delete this->player;
}

void GameState::updateInput(const float &dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("CLOSE"))))
    {
        //this->endState();
        if(!paused)
        {
            this->paused = true;
        }
        else
        {
            this->paused =  false;
        }
    }
}

void GameState::updatePlayerInput(const float &dt)
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
    
}


void GameState::update(const float & dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    
    if(!this->paused)
    {
        this->updatePlayerInput(dt);
        this->player->update(dt);
    }
    else
    {
        pmenu->update();
    }
}

void GameState::render(sf::RenderTarget * target)
{
    if(!target)
    {
        target = this->window;
    }
    this->player->render(*target);
    if(this->paused)
    {
        pmenu->render(*target);
    }
}

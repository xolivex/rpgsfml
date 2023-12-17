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
    this->pmenu->addButton("QUIT", 800.f, "quit");
}

void GameState::initFonts()
{
    if(!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
    }
}

void GameState::initTileMap()
{
    this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/image/tile/tilesheet1.png");
}

//Constructors and Destructors
GameState::GameState(StateData * state_data)
    : State(state_data)
{
    
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
    this->initFonts();
    this->initPausedMenu();
    this->initTileMap();
}
GameState::~GameState()
{
    delete pmenu;
    delete this->player;
    delete tileMap;
}

void GameState::updateTileMap()
{

}

void GameState::updateInput(const float &dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("CLOSE"))) && this->getKeytime())
    {  
        if(!this->paused)
        {
            this->pausedState();
            this->updateTileMap();
        }
        else
        {
            this->unpausedState();
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
    this->updateKeytime(dt);
    this->updateInput(dt);
    
    
    if(!this->paused)
    {
        this->updatePlayerInput(dt);
        this->player->update(dt);
    }
    else
    {
        this->pmenu->update(this->mousePosWindow);
        if(this->pmenu->isPressed("QUIT"))
        {
            this->endState();
        }
        
    }
}

void GameState::renderTileMap(sf::RenderTarget & target)
{
    tileMap->render(target);
}

void GameState::render(sf::RenderTarget * target)
{
    if(!target)
    {
        target = this->window;
    }

    this->renderTileMap(*target);

    this->player->render(*target);
    target->setView(this->window->getDefaultView());
    if(this->paused)
    {
        pmenu->render(*target);
    }
}

#include "EditorState.h"




//inicializer functions
void EditorState::initVariables()
{
    this->paused = false;
}

void EditorState::initBackground()
{

    this->background.setTexture(&this->backgroundTexture);
}

void EditorState::initKeybinds()
{
    std::ifstream ifs("Config/EditorState_keybinds.ini");

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

void EditorState::initFonts()
{
    if(!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
    }
}

void EditorState::initButtons()
{
    this->buttons["GAME_STATE"] = new gui::Button(100, 100, 150, 50, &this->font,
         "New Game", 30,
        sf::Color(70,70,70,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
        sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));

    this->buttons["SETTINGS"] = new gui::Button(100, 150, 150, 50, &this->font,
         "settings", 30,
        sf::Color(70,70,70,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
        sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));

    this->buttons["EDITOR_STATE"] = new gui::Button(100, 200, 150, 50, &this->font,
         "Editor", 30,
        sf::Color(70,70,70,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
        sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));

    this->buttons["EXIT"] = new gui::Button(100, 350, 150, 50, &this->font,
         "Quit", 30,
        sf::Color(70,70,70,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
        sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));
}
void EditorState::initPausedMenu()
{
    this->pmenu = new PausedMenu(*this->window, this->font);
    this->pmenu->addButton("QUIT", 800.f, "quit");
}
void EditorState::initTileMap()
{ 
    tileMap = new TileMap(this->stateData->gridSize, 100, 100);
}
void EditorState::initGui()
{
    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color::Transparent);
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Blue);
}
// MAINMENU
EditorState::EditorState(StateData * state_data)
    : State(state_data)
{
    this->initGui();
    this->initTileMap();
    this->initVariables();
    this->initBackground();
    this->initKeybinds();
    this->initFonts();
    this->initButtons();
    this->initPausedMenu();

    
}

EditorState::~EditorState()
{
    auto it = this->buttons.begin();
    for(it = this->buttons.begin();it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

    delete pmenu;
    
    delete tileMap;
}


void EditorState::updateInput(const float &dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("CLOSE"))) && this->getKeytime())
    {
        if(!this->paused)
        {
            this->pausedState();
        }
        else
        {
            this->unpausedState();
        }
    }
}

void EditorState::updateGui()
{
    this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
}

void EditorState::updateButtons()
{
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}

void EditorState::update(const float & dt)
{
    this->updateKeytime(dt);
    this->updateMousePositions();
    this->updateInput(dt);
    //this->updateButtons();
    if(!this->paused)
    {
        this->updateGui();
    }
    else
    {
        this->pmenu->update(this->mousePosView);
        if(this->pmenu->isPressed("QUIT"))
        {
            this->endState();
        }
    }

    

    
}

void EditorState::renderGui(sf::RenderTarget &target)
{
    target.draw(selectorRect);
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void EditorState::render(sf::RenderTarget * target)
{
    if(!target)
    {
        target = this->window;
    }

    //map
    this->renderGui(*target);

    if(this->paused)
    {   
        this->pmenu->render(*target);
    }


    //this->renderButtons(*target);

    //REMOVE LATER!!!
    /*sf::Text mouseText;
    mouseText.setPosition(this->mousePosView);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss <<"       (" << this->mousePosView.x << " . " << this->mousePosView.y << ")";
    mouseText.setString(ss.str());

    target->draw(mouseText);*/
}
#include "EditorState.h"




//inicializer functions
void EditorState::initVariables()
{
    this->paused = false;
    this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
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

void EditorState::initText()
{
    this->cursorText.setFont(this->font);
    this->cursorText.setCharacterSize(12);
    this->cursorText.setFillColor(sf::Color::White);
    
}

void EditorState::initButtons()
{
    
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
    this->selectorRect.setFillColor(sf::Color(255,255,255,150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::White);
    this->selectorRect.setTexture(this->tileMap->getTileSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    this->textureSelector = new gui::TextureSelector(10.f, 10.f, 500.f, 500.f, 
        this->stateData->gridSize,this->tileMap->getTileSheet(), this->font, "TS");
    
}
// MAINMENU
EditorState::EditorState(StateData * state_data)
    : State(state_data)
{
    this->initTileMap();
    this->initVariables();
    this->initBackground();
    this->initKeybinds();
    this->initFonts();
    this->initText();
    this->initButtons();
    this->initPausedMenu();
    this->initGui();

    
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
    delete this->textureSelector;
}

//Functions
void EditorState::updateEditorInput(const float &dt)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
    {
        if(!this->textureSelector->getActive())
        {
            this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
        }
        else
        {
            this->textureRect = this->textureSelector->getTextureRect();
        }
    }else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
    {
        if(!this->textureSelector->getActive())
            this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
    }

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
    this->textureSelector->update(this->mousePosWindow);
    if(!this->textureSelector->getActive())
    {
        this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
        this->selectorRect.setTextureRect(this->textureRect);

    }
    this->cursorText.setPosition(this->mousePosView.x + 50, this->mousePosView.y);
    this->ss.str("");
    this->ss << this->mousePosView.x << " " << this->mousePosView.y<< "\n"
             << this->textureRect.left << " " << this->textureRect.top << "\n"
             << this->mousePosGrid.x << " " << this->mousePosGrid.y;
    this->cursorText.setString(ss.str());
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
    if(!this->paused) //unpaused
    {
        this->updateGui();
        this->updateEditorInput(dt);
    }
    else //paused
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
    if(!this->textureSelector->getActive())
        target.draw(selectorRect);

    this->textureSelector->render(target);
    target.draw(this->cursorText);
    
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
    this->tileMap->render(*target);
    this->renderGui(*target);

    if(this->paused)
    {   
        this->pmenu->render(*target);
    }


    //this->renderButtons(*target);    
    

}
#include "EditorState.h"

void EditorState::initView()
{
    this->view.setSize(sf::Vector2f(this->stateData->gfxSettings->resolution.width,
                                    this->stateData->gfxSettings->resolution.height));
    this->view.setCenter(this->stateData->gfxSettings->resolution.width / 2.f,
                         this->stateData->gfxSettings->resolution.height / 2.f);
}

// inicializer functions
void EditorState::initVariables()
{
    this->paused = false;
    this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
    this->viewspeed = 500.f;
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
    this->pmenu->addButton("QUIT", 800.f, "Quit");
    this->pmenu->addButton("SAVE", 500.f, "Save");
    this->pmenu->addButton("LOAD", 400.f, "Load");
}
void EditorState::initTileMap()
{ 
    tileMap = new TileMap(this->stateData->gridSize, 50, 50, "Resources/image/tile/tilesheet1.png",1);
}
void EditorState::initGui()
{
    this->sidebar.setSize(sf::Vector2f(60.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    this->sidebar.setOutlineThickness(1.f);
    this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));

    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color(255,255,255,150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::White);
    this->selectorRect.setTexture(this->tileMap->getTileSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    this->textureSelector = new gui::TextureSelector(this->sidebar.getGlobalBounds().width + 1.f,
     this->sidebar.getGlobalBounds().top, 500.f, 500.f, 
        this->stateData->gridSize,this->tileMap->getTileSheet(), this->font, "TS");
    
}
// MAINMENU
EditorState::EditorState(StateData * state_data)
    : State(state_data)
{
    this->initView();
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
    //MOVE VIEW
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_VIEW_UP"))))
    {
        this->view.move(0.f, std::floor(-this->viewspeed * dt));
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_VIEW_DOWN"))))
    {
        this->view.move(0.f, std::floor(this->viewspeed * dt));
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_VIEW_LEFT"))))
    {
        this->view.move(std::floor(-this->viewspeed * dt), 0.f);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_VIEW_RIGHT"))))
    {
        this->view.move(std::floor(this->viewspeed * dt), 0.f);
    }

    if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
    {

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
        {
            if (!this->textureSelector->getActive())
            {
                this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);
            }
            else
            {
                this->textureRect = this->textureSelector->getTextureRect();
            }
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
        {
            if (!this->textureSelector->getActive())
                this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
        }
    }

    //keys for collision and type tile

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("TOGGLE_COLLISION"))) && this->getKeytime())
    {
        if(this->collision)
            this->collision = false;
        else
            this->collision = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("INCREASE_TYPE"))) && this->getKeytime())
    {
        ++this->type;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("DECREASE_TYPE"))) && this->getKeytime())
    {
        if(this->type > 0)
            --this->type;
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

void EditorState::updateGui(const float &dt)
{
    this->textureSelector->update(this->mousePosWindow, dt);
    if(!this->textureSelector->getActive())
    {
        this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
        this->selectorRect.setTextureRect(this->textureRect);

    }
    this->cursorText.setPosition(this->mousePosView.x + 50, this->mousePosView.y);
    this->ss.str("");
    this->ss << this->mousePosView.x << " . " << this->mousePosView.y<< "\n"
             << this->textureRect.left << " " << this->textureRect.top << "\n"
             << this->mousePosGrid.x << " " << this->mousePosGrid.y
             << "\n" << "collision: " << this->collision
             << "\n" << "type: " << this->type;
    this->cursorText.setString(ss.str());
}

void EditorState::updateButtons()
{
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosWindow);
    }
}

void EditorState::update(const float & dt)
{
    this->updateKeytime(dt);
    this->updateMousePositions(&this->view);
    this->updateInput(dt);
    //this->updateButtons();
    if(!this->paused) //unpaused
    {
        this->updateGui(dt);
        this->updateEditorInput(dt);
    }
    else //paused
    {
        this->pmenu->update(this->mousePosWindow);

        if(this->pmenu->isPressed("LOAD"))
            this->tileMap->loadFromFile("text.slmp");

        if(this->pmenu->isPressed("SAVE"))
            this->tileMap->saveToFile("text.slmp");
        
        if(this->pmenu->isPressed("QUIT"))
            this->endState();
        
        
    }

    

    
}

void EditorState::renderGui(sf::RenderTarget &target)
{
    if(!this->textureSelector->getActive())
    {
        target.setView(this->view);
        target.draw(selectorRect);

    }

    target.setView(this->window->getDefaultView());
    this->textureSelector->render(target);
    target.draw(this->sidebar);

    target.setView(this->view);
    target.draw(this->cursorText);
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
    target.setView(this->view);
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
    target->setView(this->view);
    this->tileMap->render(*target);

    target->setView(this->window->getDefaultView());
    this->renderButtons(*target);

    this->renderGui(*target);

    if(this->paused)
    {   
        target->setView(this->window->getDefaultView());
        this->pmenu->render(*target);
    }


    //this->renderButtons(*target);    
    

}
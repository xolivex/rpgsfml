#include "MainMenuState.h"


//inicializer functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
    this->background.setSize(sf::Vector2f(this->window->getSize()));

    if(!this->backgroundTexture.loadFromFile("Resources/image/background/bg.png"))
    {
        throw("MAIN::MANUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
    }

    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initFonts()
{
    if(!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMANUSTATE::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initButtons()
{
    this->buttons["GAME_STATE"] = new Button(100.f, 100.f, 150.f, 50.f, &this->font,
         "New Game", 30,
        sf::Color(150,150,150,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
        sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));

    this->buttons["SETTINGS_STATE"] = new Button(100.f, 150.f, 150.f, 50.f, &this->font,
         "settings", 30,
        sf::Color(150,150,150,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
        sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));

    this->buttons["EDITOR_STATE"] = new Button(100.f, 200.f, 150.f, 50.f, &this->font,
         "Editor", 30,
        sf::Color(150,150,150,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
        sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));

    this->buttons["EXIT"] = new Button(100.f, 350.f, 150.f, 50.f, &this->font,
         "Quit", 30,
        sf::Color(150,150,150,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
        sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));
}
//MAINMENU
MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*> * states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initKeybinds();
    this->initFonts();
    this->initButtons();

    
}

MainMenuState::~MainMenuState()
{
    auto it = this->buttons.begin();
    for(it = this->buttons.begin();it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}


void MainMenuState::updateInput(const float &dt)
{
    
}
   


void MainMenuState::updateButtons()
{
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    //GAME
    if(this->buttons["GAME_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }

    //SETTINGS
    if(this->buttons["SETTINGS_STATE"]->isPressed())
    {
        this->states->push(new SettingsState(this->window, this->supportedKeys, this->states));
    }
    
    //EDITOR
    if(this->buttons["EDITOR_STATE"]->isPressed())
    {
        this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
    }

    //EXIT
    if(this->buttons["EXIT"]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::update(const float & dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();


    

    
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget * target)
{
    if(!target)
    {
        target = this->window;
    }
    target->draw(background);
    this->renderButtons(*target);

    //REMOVE LATER!!!
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss <<"       (" << this->mousePosView.x << " . " << this->mousePosView.y << ")";
    mouseText.setString(ss.str());

    target->draw(mouseText);
}

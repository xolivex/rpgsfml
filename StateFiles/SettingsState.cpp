#include "SettingsState.h"


//inicializer functions
void SettingsState::initVariables()
{
}

void SettingsState::initBackground()
{
    this->background.setSize(sf::Vector2f(this->window->getSize()));

    if(!this->backgroundTexture.loadFromFile("Resources/image/background/bg.png"))
    {
        throw("MAIN::SETTINGSSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
    }

    this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initKeybinds()
{
    std::ifstream ifs("Config/settingsstate_keybinds.ini");

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

void SettingsState::initFonts()
{
    if(!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::SETTINGSSTATE::COULD NOT LOAD FONT");
    }
}

void SettingsState::initButtons()
{
    

    this->buttons["EXIT"] = new Button(100.f, 350.f, 150.f, 50.f, &this->font,
         "Quit", 30,
        sf::Color(150,150,150,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
        sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));
}

//MAINMENU
SettingsState::SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*> * states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initKeybinds();
    this->initFonts();
    this->initButtons();

    
}

SettingsState::~SettingsState()
{
    auto it = this->buttons.begin();
    for(it = this->buttons.begin();it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}


void SettingsState::updateInput(const float &dt)
{
    
}
   


void SettingsState::updateButtons()
{
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }


    if(this->buttons["EXIT"]->isPressed())
    {
        this->endState();
    }
}

void SettingsState::update(const float & dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();

}

void SettingsState::renderButtons(sf::RenderTarget& target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget * target)
{
    if(!target)
    {
        target = this->window;
    }
    target->draw(background);
    this->renderButtons(*target);
}

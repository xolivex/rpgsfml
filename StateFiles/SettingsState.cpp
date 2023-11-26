#include "SettingsState.h"

// inicializer functions
void SettingsState::initVariables()
{
    this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
{
    this->background.setSize(sf::Vector2f(this->window->getSize()));

    if (!this->backgroundTexture.loadFromFile("Resources/image/background/bg.png"))
    {
        throw("MAIN::SETTINGSSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
    }

    this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initKeybinds()
{
    std::ifstream ifs("Config/settingsstate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
        {
            this->Keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void SettingsState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::SETTINGSSTATE::COULD NOT LOAD FONT");
    }
}

void SettingsState::initGui()
{

    this->buttons["APPLY"] = new gui::Button(
        600.f, 600.f, 150.f, 50.f,
        &this->font, "Apply", 30,
        sf::Color(150, 150, 150, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["EXIT"] = new gui::Button(
        750.f, 600.f, 150.f, 50.f,
        &this->font, "Back", 30,
        sf::Color(150, 150, 150, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    std::vector<std::string> modes_str;
    for (auto &i : this->modes)
    {
        modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
    }
    this->dropDownLists["RESOLUTION"] = new gui::DropDownList(500.f, 100.f, 200.f, 50.f, this->font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
    this->settingsText.setFont(this->font);
    this->settingsText.setCharacterSize(50);
    this->settingsText.setPosition(100.f, 100.f);
    this->settingsText.setString(
        "Resolutions \nFullScreen \nFrameRate \nVerticalSync \nAntiAliasing");
}

// MAINMENU
SettingsState::SettingsState(StateData * state_data)
    : State(state_data)
{
    this->initVariables();
    this->initBackground();
    this->initKeybinds();
    this->initFonts();
    this->initGui();
    this->initText();
}

SettingsState::~SettingsState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

    auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
    {
        delete it2->second;
    }
}

void SettingsState::updateInput(const float &dt)
{
}

void SettingsState::updateGui(const float &dt)
{
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    for (auto &it : this->dropDownLists)
    {
        it.second->update(this->mousePosView, dt);
    }

    if (this->buttons["APPLY"]->isPressed() && this->dropDownLists["RESOLUTION"]->getkeyTime())
    {
        this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];

        this->window->create(this->stateData->gfxSettings->resolution,
                             this->stateData->gfxSettings->title,
                             sf::Style::Titlebar | sf::Style::Close);
    }

    if (this->buttons["EXIT"]->isPressed())
    {
        this->endState();
    }
}

void SettingsState::update(const float &dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget &target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }

    for (auto &it : this->dropDownLists)
    {
        it.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget *target)
{
    if (!target)
    {
        target = this->window;
    }
    target->draw(this->background);
    target->draw(this->settingsText);
    this->renderGui(*target);
}

#include "Game.h"

// static functions
// initializer functions

void Game::initVariables()
{
    this->window = NULL;
    this->dt = 0.f;
    this->gridSize = 100.f;
}

void Game::initGraphicsSettings()
{
    this->gfxSettings.LoadFromFile("Config/graphics.ini");
}

void Game::initGameWindow()
{

    if (this->gfxSettings.fullscreen)
    {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution,
                                            this->gfxSettings.title, sf::Style::Fullscreen, this->gfxSettings.contextSettings);
    }
    else
    {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution,
                                            this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
    }

    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
    
}

void Game::initStates()
{
    this->states.push(new MainMenuState(&this->stateData));
}
//--
void Game::initKeys()
{
    // foi usado apenas pra deixar tudo maiusculo
    // scripts
    /*std::ifstream ifile("Config/keys.ini");
    std::ofstream ofile("Config/list.ini");
    std::string line;
    int iter = 0;
    while(ifile >> line)
    {
    for (size_t i = 0; i < line.length(); i++)
    {
        line[i] = std::toupper(line[i]);
    }
        ofile << line << " " << iter <<std::endl;
        iter++;
    }
    ofile.close();
    ifile.close();*/

    std::ifstream ifs("Config/supported_keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int keyvalue = 0;

        while (ifs >> key >> keyvalue)
        {
            this->supportedKeys[key] = keyvalue;
        }
    }

    ifs.close();

    // DEBUG REMOVE LATER!
    /*for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }*/
}
// constructor and destructor
Game::Game()
{
    this->initVariables();
    this->initGraphicsSettings();
    this->initGameWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{
    delete this->window;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}
void Game::endApplication()
{
    std::cout << "Ending Application..."
              << "\n";
}

void Game::dtUpdate()
{
    this->dt = this->dtClock.restart().asSeconds();
}
// functions
void Game::updateSFMLEvents()
{
    if (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->dtUpdate();
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    // Aplication end
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear(sf::Color::Black);
    // render items
    if (!this->states.empty())
        this->states.top()->render(this->window);

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }
}

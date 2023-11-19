#include "Game.h"



// static functions
//initializer functions

void Game::initVariables()
{
    this->window = NULL;
    this->fullscreen = false;
    this->dt = 0.f;
}

void Game::initGameWindow() 
{
    initVariables();
    std::ifstream ifs("Config/window.ini");
    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned short framerate_limit = 60;
    bool vertical_sync_enabled = false;
    unsigned short antialiasing_level = 0;

    if(ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
        //define the resolution of workspace
        
    }
    ifs.close();

    this->fullscreen = fullscreen;
    this->window_settings.antialiasingLevel = antialiasing_level;
    if(this->fullscreen){
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->window_settings);
    }
    else{
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->window_settings);
    }

    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}
//--
void Game::initKeys()
{
    //foi usado apenas pra deixar tudo maiusculo
    //scripts
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

    if(ifs.is_open())
    {
        std::string key = "";
        int keyvalue = 0;

        while(ifs >> key >> keyvalue)
        {
            this->supportedKeys[key] = keyvalue;
        }
        std::cout << "saiu" <<std::endl;
    }

    ifs.close();

//DEBUG REMOVE LATER!
    /*for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }*/

}
// constructor and destructor
Game::Game()
{
    this->initGameWindow();
    this->initKeys();
    this->initStates();
    
}

Game::~Game()
{
    delete this->window;
    while(!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}
void Game::endApplication()
{
    std::cout << "Ending Application..." << "\n";
}

void Game::dtUpdate()
{
    this->dt = this->dtClock.restart().asSeconds();
     
}
// functions
void Game::updateSFMLEvents()
{
    if(this->window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->dtUpdate();
    this->updateSFMLEvents();

    if(!this->states.empty()){
        this->states.top()->update(this->dt);
        if(this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    //Aplication end
    else{
        this->endApplication();
        this->window->close();
    }

}

void Game::render()
{
    this->window->clear(sf::Color::Black);
        //render items
        if(!this->states.empty())
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

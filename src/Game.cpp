#include "../headers/Game.hpp"


// static functions
//initializer functions
void Game::initGameWindow()
{
    std::ifstream ifs("../Config/window.ini");
    std::string title = "None";
    sf::VideoMode window_bounds(800,600);
    unsigned short framerate_limit = 120;
    bool vertical_sync_enabled = false;
    if(ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;

    }
    this->window = new sf::RenderWindow(window_bounds,title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
    this->states.push(new GameState(this->window, &this->supportedKeys));
}
//--
void Game::initKeys()
{
    supportedKeys.emplace("ESC", sf::Keyboard::Key::Escape);
    supportedKeys.emplace("A", sf::Keyboard::Key::A);
    supportedKeys.emplace("D", sf::Keyboard::Key::D);
    supportedKeys.emplace("W", sf::Keyboard::Key::W);
    supportedKeys.emplace("S", sf::Keyboard::Key::S);
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
    //system("cls");
    //std::cout << dt <<std::endl;
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
    this->window->clear(sf::Color::White);
        //render items
        if(!this->states.empty())
            this->states.top()->render(this->window);

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->dtUpdate();
        this->update();
        this->render();
        
    }
    
}

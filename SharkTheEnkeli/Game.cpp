#include "Game.h"
#include "VersionCommand.h"
#include "HelpCommand.h"

void Game::pollEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
            window.close();

    }
}

void Game::update()
{
    ImGui::SFML::Update(window, deltaClock.restart());
    console->update();
    
}

void Game::draw()
{

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    window.clear();
    window.draw(shape);
    ImGui::SFML::Render(window);
    window.display();
}

Game::Game(int argc, char* argv[])
{
    state = MAINMENU;
    console->setGame(this);
    // Printing the number of arguments
    std::cout << "Number of arguments: " << argc << std::endl;

    // Printing each argument
    std::cout << "Arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }

    const std::string str = "-debug";

    for (size_t i = 0; i < argc; i++)
    {
        if (!str.compare(argv[i])) {
            debug = true;
            console->print("debug mode active!");
            console->print("Welcome to Shark The Enkeli debug console");
        }
    }
}

Game::Game() 
{
    state = MAINMENU;
}
Game::~Game()
{
}

void Game::run()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    window.create(sf::VideoMode(1280, 720), "Shark The Enkeli", sf::Style::Default, settings);
    ImGui::SFML::Init(window);

    while (window.isOpen())
    {
        pollEvents();
        update();
        draw();
    }
    ImGui::SFML::Shutdown();
}

ILevel* Game::getCurrentLevel()
{
    return currentLevel;
}

std::string Game::getVersion()
{
    return version;
}

bool Game::executeCommand(Command* command)
{
    VersionCommand* versionCmd = dynamic_cast<VersionCommand*>(command);
    if (versionCmd) {
        versionCmd->execute();
        return true;
    }
    HelpCommand* helpCmd = dynamic_cast<HelpCommand*>(command);
    if (helpCmd) {
        helpCmd->execute();
        return true;
    }
    return false;
}


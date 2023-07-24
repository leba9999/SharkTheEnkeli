#include "Game.h"

#include "Commands/VersionCommand.h"
#include "Commands/CloseGameCommand.h"
#include "Commands/FullscreenCommand.h"

void Game::pollEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::LostFocus) {
            console->print("Lost Focus");
            state = PAUSED;
            focus = false;
        }
        if (event.type == sf::Event::GainedFocus) {
            console->print("Gained Focus");
            focus = true;
        }
        currentLevel->pollEvents(event);
    }
}

void Game::update()
{
    ImGui::SFML::Update(window, deltaClock.restart());
    currentLevel->update();
    console->update();
}

void Game::draw()
{
    window.clear();
    window.draw(*currentLevel);
    ImGui::SFML::Render(window);
    window.display();
}

void Game::init()
{
    state = RUNNING;
    console->setGame(this);
    debug = false;
    fullscreen = false;
    vsync = false;
    resetWindow = false;
    levelId = 0;
}

void Game::createWindow()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    if (fullscreen) {
        window.create(sf::VideoMode(1280, 720), "Shark The Enkeli", sf::Style::Fullscreen, settings);
    }
    else {
        window.create(sf::VideoMode(1280, 720), "Shark The Enkeli", sf::Style::Default, settings);
    }
    window.setVerticalSyncEnabled(vsync);
}

Game::Game(int argc, char* argv[])
{
    init();
    const std::string str[] = { "-debug", "-windowed", "-fullscreen", "-vsync"};
    for (size_t i = 0; i < argc; i++)
    {
        if (!str[0].compare(argv[i])) {
            debug = true;
            console->print("debug mode active!");
            console->print("Welcome to Shark The Enkeli debug console", ImVec4(1.0f, 0.8f, 0.01f, 1.0f));
            console->print("Enter ? to see commands", ImVec4(1.0f, 0.8f, 0.01f, 1.0f));
        }
        if (!str[1].compare(argv[i])) {
            fullscreen = false;
            console->print("windowed mode active!");
        }
        if (!str[2].compare(argv[i])) {
            fullscreen = true;
            console->print("fullscreen mode active!");
        }
        if (!str[3].compare(argv[i])) {
            vsync = true;
            console->print("vsync active!");
        }
    }
}

Game::~Game()
{
    delete console;
    delete currentLevel;
}

void Game::run()
{
    do {
        resetWindow = false;
        createWindow();
        ImGui::SFML::Init(window);
        while (window.isOpen())
        {
            pollEvents();
            update();
            draw();
        }
        ImGui::SFML::Shutdown();
    } while (resetWindow);
}

void Game::close()
{
    window.close();
}

void Game::resetwindow()
{
    resetWindow = true;
    close();
}

bool Game::getFocus()
{
    return focus;
}

sf::RenderWindow &Game::getWindow()
{
    return window;
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
    FullscreenCommand* fullscreenCmd = dynamic_cast<FullscreenCommand*>(command);
    if (fullscreenCmd) {
        fullscreenCmd->enableFullscreen(&fullscreen);
        return fullscreenCmd->execute();
    }
    return command->execute();
}

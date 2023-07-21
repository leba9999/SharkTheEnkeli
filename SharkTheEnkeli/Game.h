#include <iostream>
#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include "Console.h"
#include "Command.h"
#include "ILevel.h"
#include "MainMenu.h"
#pragma once
class Game
{
public:
	enum States { MAINMENU, PAUSED, LEVEL_1, LEVEL_2, LEVEL_3};
	States state;
	Game();
	Game(int argc, char* argv[]);
	void run();
	ILevel* getCurrentLevel();
	std::string getVersion();
	bool executeCommand(Command* command);
	~Game();
private:
	const std::string version = "1.0.0";
	Console* console = Console::getInstance();
	sf::RenderWindow window;
	bool debug = false;
	sf::Clock deltaClock;

	ILevel* currentLevel = new MainMenu();
	void pollEvents();
	void update();
	void draw();
};


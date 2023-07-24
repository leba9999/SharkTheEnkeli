#include <iostream>
#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include "Console.h"
#include "ILevel.h"
#include "MainMenu.h"
#pragma once
class Game
{
public:
	enum States { PAUSED, RUNNING};
	Game(int argc, char* argv[]);
	void run();
	void close();
	void resetwindow();
	void reset();
	bool getFocus();
	sf::RenderWindow &getWindow();
	ILevel* getCurrentLevel();
	std::string getVersion();
	bool executeCommand(Command* command);
	~Game();
private:
	void pollEvents();
	void update();
	void draw();
	void init();
	void createWindow();

	sf::RenderWindow window;
	sf::Clock deltaClock;
	std::vector<sf::Drawable> drawStack;
	States state;

	int levelId;

	bool debug;
	bool resetWindow;
	bool vsync;
	bool fullscreen;
	bool focus;

	const std::string version = "1.0.0";
	Console* console = Console::getInstance();
	ILevel* currentLevel = new MainMenu(this);
};


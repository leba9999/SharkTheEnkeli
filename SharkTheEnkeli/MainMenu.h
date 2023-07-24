#pragma once
#include "ILevel.h"
#include "Console.h"
class Game;
class MainMenu : public ILevel
{
public:

	MainMenu(Game* game);
	
	// Inherited via ILevel
	void initialize();
	void update();
	void pollEvents(sf::Event event);
private:
	// Inherited via ILevel
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	Game* game;
	sf::Font font;
	sf::Text start;
	sf::Text exit;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	Console* console = Console::getInstance();
};


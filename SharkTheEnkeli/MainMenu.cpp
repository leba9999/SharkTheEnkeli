#include "MainMenu.h"
#include "Game.h"

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background);
	target.draw(start);
	target.draw(exit);
}

MainMenu::MainMenu(Game* game)
{
	this->game = game;
	initialize();
}

void MainMenu::initialize()
{
	console->print("Initializing level...");
	if (!font.loadFromFile("resources\\fonts\\cour.ttf"))
	{
		console->print("Cannot load resource: cour.ttf");
	}
	if (!backgroundTexture.loadFromFile("resources\\textures\\clouds.png"))
	{
		console->print("Cannot load resource: clouds.png");
	}
	background.setTexture(backgroundTexture);
	start.setFont(font);
	exit.setFont(font);

	start.setString("Start the game");
	exit.setString("Exit the game");

	start.setCharacterSize(34);
	exit.setCharacterSize(34);


}

void MainMenu::update()
{
	int windowX = game->getWindow().getView().getSize().x;
	int windowY = game->getWindow().getView().getSize().y;
	sf::Vector2f viewCenter = game->getWindow().getView().getCenter();
	background.setPosition(viewCenter.x - windowX/2, viewCenter.y - windowY/2);
	background.setScale(2, 2);
	if (game) {
		start.setPosition(sf::Vector2f((windowX / 2) - (start.getLocalBounds().getSize().x / 2), (windowY / 2) - (start.getLocalBounds().getSize().y)));
		exit.setPosition(sf::Vector2f((windowX / 2) - (exit.getLocalBounds().getSize().x / 2), (windowY / 2) + (start.getLocalBounds().getSize().y)));
	}
}

void MainMenu::pollEvents(sf::Event event)
{
}

#pragma once
#include "ILevel.h"
class MainMenu : public ILevel
{
private:
	// Inherited via ILevel
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:

	MainMenu();

	// Inherited via ILevel
	void initialize();
	void update();
	void pollEvents();
};


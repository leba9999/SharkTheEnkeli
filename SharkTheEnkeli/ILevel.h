#pragma once
#include "Player.h"

#include <SFML/Graphics/Drawable.hpp>

class ILevel : sf::Drawable {
protected:
	int state;
	Player player;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0 ;
public:
	virtual ~ILevel() {};
	virtual void setPlayer(Player& player) {
		this->player = player;
	};
	virtual Player getPlayer() {
		return this->player;
	};
	virtual void setState(int state) {
		this->state = state;
	};
	virtual int getState() {
		return this->state;
	};
	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual void pollEvents() = 0;
};
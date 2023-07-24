#include "FullscreenCommand.h"
#include "../Game.h"

FullscreenCommand::FullscreenCommand(Game* game, bool enabled)
{
    this->game = game;
	this->enabled = enabled;
	this->fullscreen = nullptr;
}

FullscreenCommand::FullscreenCommand()
{
	this->enabled = true;
	this->fullscreen = nullptr;
}

FullscreenCommand::~FullscreenCommand()
{
	delete fullscreen;
}

void FullscreenCommand::setGame(Game* game)
{
    this->game = game;
}

void FullscreenCommand::enableFullscreen(bool *variable)
{
	this->fullscreen = variable;
}

bool FullscreenCommand::execute()
{
	if (game) {
		(*fullscreen) = enabled;
		game->resetwindow();
		return true;
	}
	return false;
}

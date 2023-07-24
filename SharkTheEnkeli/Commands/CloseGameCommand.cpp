#include "CloseGameCommand.h"
#include "../Game.h"

CloseGameCommand::CloseGameCommand(Game* game)
{
	this->game = game;
}

CloseGameCommand::CloseGameCommand()
{
}

void CloseGameCommand::setGame(Game* game)
{
	this->game = game;
}

bool CloseGameCommand::execute()
{
	if (game) {
		game->close();
		return true;
	}
	return false;
}

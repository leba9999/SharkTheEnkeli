#pragma once
#include "Command.h"
class Game;

class CloseGameCommand : public Command
{
private:
	Game* game;
public:
	CloseGameCommand(Game* game);
	CloseGameCommand();
	void setGame(Game* game);
	// Inherited via Command
	virtual bool execute() override;
};


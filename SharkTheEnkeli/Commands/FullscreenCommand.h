#pragma once
#include "Command.h"
class Game;
class FullscreenCommand : public Command
{
public:
	FullscreenCommand(Game* game, bool enabled);
	FullscreenCommand();
	~FullscreenCommand();
	void setGame(Game* game);
	void enableFullscreen(bool *variable);
	// Inherited via Command
	virtual bool execute() override;
private:
	Game* game;
	bool* fullscreen;
	bool enabled;
};


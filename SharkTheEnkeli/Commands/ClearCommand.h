#pragma once
#include "Command.h"
#include "../Console.h"
class ClearCommand : public Command
{
public:
	virtual bool execute() override;
private:
	Console* console = Console::getInstance();
};


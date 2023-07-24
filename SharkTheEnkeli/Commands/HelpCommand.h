#pragma once
#include "Command.h"
#include "../Console.h"
#include <string>
class HelpCommand : public Command
{

public:
	bool execute() override;

private:
	Console* console = Console::getInstance();
public:

	HelpCommand();
};


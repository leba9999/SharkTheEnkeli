#pragma once
#include "Command.h"
#include "Console.h"
#include <string>
class HelpCommand : public Command
{

public:
	void execute() override;

private:
	Console* console = Console::getInstance();
public:

	HelpCommand() = default;
};


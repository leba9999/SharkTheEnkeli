#pragma once
#include "Command.h"
#include "Console.h"
#include <string>
class VersionCommand : public Command
{
public:
	VersionCommand(std::string version);
	void execute() override;

private:
	std::string version;
	Console* console = Console::getInstance();
};


#include "HelpCommand.h"

bool HelpCommand::execute()
{
	console->print("Avaible commands:", ImVec4(1.0f, 0.8f, 0.01f, 1.0f));
	console->print("Help - show avaible commands");
	console->print("? - show avaible commands");
	console->print("Clear - Clear console");
	console->print("Version - Shows game version");
	console->print("Level - select level");
	return true;
}

HelpCommand::HelpCommand()
{
	this->setShortDescription("shows avaible commands");
	this->setDescription("shows avaible commands");
}

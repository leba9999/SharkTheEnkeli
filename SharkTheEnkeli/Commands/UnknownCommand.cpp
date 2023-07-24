#include "UnknownCommand.h"

UnknownCommand::UnknownCommand()
{
	this->setShortDescription("Unknown command");
	this->setDescription("Unknown command: Command cannot be found");
}

bool UnknownCommand::execute()
{
	//Empty Command
	return false;
}

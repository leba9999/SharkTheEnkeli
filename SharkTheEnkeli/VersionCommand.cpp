#include "VersionCommand.h"

VersionCommand::VersionCommand(std::string version)
{
	this->version = version;
}

void VersionCommand::execute()
{
	console->print(version);
}

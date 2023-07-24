#include "VersionCommand.h"

VersionCommand::VersionCommand(std::string version)
{
	this->version = version;
	this->setShortDescription("Shows game version number");
	this->setDescription("Shows game version number");
}

VersionCommand::VersionCommand()
{
}

void VersionCommand::setVersion(std::string version)
{
	this->version = version;
}

bool VersionCommand::execute()
{
	console->print(version);
	return true;
}

#include "HelpCommand.h"

void HelpCommand::execute()
{
	console->print("Avaible commands:");
	console->print("Help");
	console->print("?");
	console->print("Version");
	console->print("level");
}

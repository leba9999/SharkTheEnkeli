#include "ClearCommand.h"

bool ClearCommand::execute()
{
	console->clear();
	return true;
}

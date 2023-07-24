#pragma once
#include "Command.h"
class UnknownCommand : public Command
{
public:
	UnknownCommand();
	bool execute() override;

};


#pragma once

#include "Command.h"

namespace Leviathan
{
	class TickCommand : public Command
	{
	public:
		TickCommand();
		virtual bool Do();
		virtual bool Undo();

	private:

	};
}
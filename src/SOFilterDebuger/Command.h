#pragma once

namespace Leviathan
{
	/*
		Abstract command base class for [Do/Undo stack] schema
	*/

	class Command
	{
	public:
		virtual bool Do() = 0;
		virtual bool Undo() = 0;
	};
}
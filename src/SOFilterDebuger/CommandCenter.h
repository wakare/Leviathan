#pragma once

#include <vector>
#include <list>
#include <mutex>
#include "LPtr.h"
#include "Command.h"
#include "ThreadRecorder.h"

namespace Leviathan
{
	class CommandStackStruct
	{
	public:
		CommandStackStruct(unsigned size);

		/*
			if stack are not full
				push command will push back command to vector
			else
				update the oldest element value to command
		*/
		bool PushCompletedCommand(LPtr<Command> pCommand);
		bool UndoLastCompletedCommand();

	private:
		unsigned m_stack_size;

		std::list<LPtr<Command>> m_stack;
	};

	class CommandCenter : public ThreadRecorder
	{
	public:
		CommandCenter(unsigned command_stack_size = 100);

		void SetCommandStackSize(unsigned command_stack_size);
		bool PostCommand(LPtr<Command> pCommand);
		void DoCommands();
		void UndoOneCommand();

	private:
		std::mutex m_lock;
		std::vector<LPtr<Command>> m_unfinished_commands;
		LPtr<CommandStackStruct> m_command_stack;
	};
}
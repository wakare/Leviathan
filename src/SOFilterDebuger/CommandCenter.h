#pragma once

#include <vector>
#include <list>
#include <mutex>
#include "LSPtr.h"
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
		bool PushCompletedCommand(LSPtr<Command> pCommand);
		bool UndoLastCompletedCommand();

	private:
		unsigned m_stack_size;

		std::list<LSPtr<Command>> m_stack;
	};

	class CommandCenter : public ThreadRecorder
	{
	public:
		CommandCenter(unsigned command_stack_size = 100);

		void SetCommandStackSize(unsigned command_stack_size);
		bool PostCommand(LSPtr<Command> pCommand);
		void DoCommands();
		void UndoOneCommand();

	private:
		std::mutex m_lock;
		std::vector<LSPtr<Command>> m_unfinished_commands;
		LSPtr<CommandStackStruct> m_command_stack;
	};
}
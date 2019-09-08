#include "CommandCenter.h"

namespace Leviathan
{
	CommandStackStruct::CommandStackStruct(unsigned size)
		: m_stack_size(size)
	{
		
	}

	bool CommandStackStruct::PushCompletedCommand(LSPtr<Command> pCommand)
	{
		// Full stack?
		bool full = m_stack.size() == m_stack_size;

		if (full)
		{
			// Remove stack-top element
			m_stack.pop_front();
		}

		m_stack.push_back(pCommand);

		return true;
	}

	bool CommandStackStruct::UndoLastCompletedCommand()
	{
		EXIT_IF_FALSE(m_stack.size() > 0);

		auto& lastCommand = (--m_stack.end());
		auto result = (*lastCommand)->Undo();
		
		// If a command undo failed, we can not remove this command from command stack
		EXIT_IF_FALSE(result);

		m_stack.erase(lastCommand);

		return true;
	}

	CommandCenter::CommandCenter(unsigned command_stack_size)
	{
		SetCommandStackSize(command_stack_size);
	}

	void CommandCenter::SetCommandStackSize(unsigned command_stack_size)
	{
		m_command_stack.Reset(new CommandStackStruct(command_stack_size));
	}

	bool CommandCenter::PostCommand(LSPtr<Command> pCommand)
	{
		if (IsCreateThread())
		{
			m_unfinished_commands.push_back(pCommand);
		}
		
		else
		{
			std::lock_guard<std::mutex> lock(m_lock);
			m_unfinished_commands.push_back(pCommand);
		}

		return true;
	}

	/*
		DoCommand must be called form the thread which create command center	
	*/
	void CommandCenter::DoCommands()
	{
		LEV_ASSERT(IsCreateThread());

		if (!IsCreateThread())
		{
			return;
		}

		for (auto& command : m_unfinished_commands)
		{
			command->Do();
			m_command_stack->PushCompletedCommand(command);
		}

		// Clear unfinished task list
		m_unfinished_commands.clear();
	}

	/*
		UndoOneCommand must be called form the thread which create command center
	*/
	void CommandCenter::UndoOneCommand()
	{
		LEV_ASSERT(IsCreateThread());

		if (!IsCreateThread())
		{
			return;
		}

		m_command_stack->UndoLastCompletedCommand();
	}
}
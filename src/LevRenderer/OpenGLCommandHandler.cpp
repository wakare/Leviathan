#include "OpenGLCommandHandler.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLCommandHandler::OpenGLCommandHandler(OpenGLCommandHandlerType handler_type)
			: m_handler_type(handler_type)
		{
		}

		/*bool OpenGLCommandHandler::PushCommand(LSPtr<IOpenGLCommand> command)
		{
			m_command_buffer.push_back(command);

			if (command->GetCommandType() == OpenGLCommandType::EOCT_SYNC)
			{
				FlushBuffer();
			}

			return true;
		}*/

		bool OpenGLCommandHandler::PushCommand(LSPtr<IOpenGLCommand> command)
		{
			command->Execute();
			return true;
		}

		bool OpenGLCommandHandler::FlushBuffer()
		{
			for (const auto& command : m_command_buffer)
			{
				if (!command->Execute())
				{
					return false;
				}
			}

			return true;
		}
	}
}
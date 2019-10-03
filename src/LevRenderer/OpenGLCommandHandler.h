#pragma once

#include "IOpenGLCommand.h"
#include <vector>

namespace Leviathan
{
	namespace Renderer
	{
		enum OpenGLCommandHandlerType
		{
			EOCHT_NON_EXTRA_THREAD,
			EOCHT_EXTRA_THREAD,
		};

		class OpenGLCommandHandler
		{
		public:
			OpenGLCommandHandler(OpenGLCommandHandlerType handler_type);

			bool PushCommand(LSPtr<IOpenGLCommand> command);
			bool FlushBuffer();

		private:
			OpenGLCommandHandlerType m_handler_type;

			std::vector<LSPtr<IOpenGLCommand>> m_command_buffer;
		};
	}
}



#pragma once
#include "LSPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		enum OpenGLCommandType
		{
			EOCT_SYNC,
			EOCT_ASYNC,
		};

		class IOpenGLCommand
		{
			public:
				virtual ~IOpenGLCommand() = default;
				virtual bool Execute() = 0;
				virtual OpenGLCommandType GetCommandType() const = 0;
		};

		template <typename LAMBDA_BODY_TYPE>
		class OpenGLCommandImpl : public IOpenGLCommand
		{
		public:
			OpenGLCommandImpl(LAMBDA_BODY_TYPE lambda_body, OpenGLCommandType command_type)
				: m_lambda_body(lambda_body)
				, m_command_type(command_type)
			{
				
			};

			bool Execute() override
			{
				m_lambda_body();
				return true;
			}

			OpenGLCommandType GetCommandType() const override
			{
				return m_command_type;
			};

		private:
			LAMBDA_BODY_TYPE m_lambda_body;
			OpenGLCommandType m_command_type;
		};

		template<typename LAMBDA_BODY_TYPE>
		bool CreateCommand(LAMBDA_BODY_TYPE lambda_body, OpenGLCommandType command_type, LSPtr<IOpenGLCommand>& command)
		{
			command.Reset(new OpenGLCommandImpl<LAMBDA_BODY_TYPE>(lambda_body, command_type));
			return true;
		}
	}
}

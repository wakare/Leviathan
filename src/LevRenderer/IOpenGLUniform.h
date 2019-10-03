#pragma once
#include "Gl/glew.h"
#include "IOpenGLResource.h"
#include <string>

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLObjectManager;

		class IOpenGLUniform : public IOpenGLResource
		{
		public:
			IOpenGLUniform(OpenGLObjectManager& object_manager)
				: m_object_manager(object_manager)
			{
				
			}

			virtual bool Apply(GLuint program) = 0;
			virtual bool UnApply(GLuint program) = 0;

			virtual const std::string& GetUniformName() const = 0;

			virtual ~IOpenGLUniform() = default;

		protected:
			OpenGLObjectManager& m_object_manager;
		};

#define IOU_PUSH_SYNC_RENDER_COMMAND(command) m_object_manager.PushRenderCommand([&] {command;}, OpenGLCommandType::EOCT_SYNC);
#define IOU_PUSH_ASYNC_RENDER_COMMAND(command) m_object_manager.PushRenderCommand([&] {command;}, OpenGLCommandType::EOCT_ASYNC);
	}
}

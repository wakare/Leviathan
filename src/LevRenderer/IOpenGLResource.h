#pragma once

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLUniform;
		class IOpenGLObject;
		class IOpenGLRenderResource;
		class OpenGLResourceManager;

		class IOpenGLResource
		{
		public:
			IOpenGLResource(OpenGLResourceManager& resource_manager)
				: m_resource_manager(resource_manager)
			{
				
			}

			virtual ~IOpenGLResource() = default;

			/*
			 * Avoid dynamic conversion
			 */

			virtual IOpenGLUniform* ToOpenGLUniform() { return nullptr; }
			virtual IOpenGLObject* ToOpenGLObject() { return nullptr; }
			virtual IOpenGLRenderResource* ToOpenGLRenderEntry() { return nullptr; }

		protected:
			OpenGLResourceManager& m_resource_manager;
		};

#define IOR_PUSH_SYNC_RENDER_COMMAND(command)	m_resource_manager.PushRenderCommand([&] {command;}, OpenGLCommandType::EOCT_SYNC);
#define IOR_PUSH_ASYNC_RENDER_COMMAND(command)	m_resource_manager.PushRenderCommand([&] {command;}, OpenGLCommandType::EOCT_ASYNC);
#define IOR_FLUSH_RENDER_COMMAND(command)		m_resource_manager.FlushRenderCommand();
	}
}
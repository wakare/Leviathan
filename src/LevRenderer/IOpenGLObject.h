#pragma once
#include "IOpenGLResource.h"
#include "LevTokenDispatch.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLTextureObject;
		class OpenGLObjectManager;

		typedef unsigned OpenGLObjectHandle;

		class IOpenGLObject : public Renderer::IOpenGLResource
		{
		public:
			IOpenGLObject(OpenGLObjectManager& object_manager) 
				: m_object_manager(object_manager)
				, m_object_handle(LevTokenDispatch<IOpenGLObject, OpenGLObjectHandle>::GetIncrementToken())
			{
			}

			virtual ~IOpenGLObject() = default;

			OpenGLObjectHandle GetOpenGLObjectHandle() const { return m_object_handle; }
			virtual IOpenGLTextureObject* ToOpenGLTextureObject() { return nullptr; }

			IOpenGLObject* ToOpenGLObject() override { return this; };

			bool Equals(const IOpenGLObject& lhs) const { return m_object_handle == lhs.m_object_handle; }

		protected:
			OpenGLObjectManager& m_object_manager;
			OpenGLObjectHandle m_object_handle;
		};

#define IOO_PUSH_SYNC_RENDER_COMMAND(command) m_object_manager.PushRenderCommand([&] {command;}, OpenGLCommandType::EOCT_SYNC);
#define IOO_PUSH_ASYNC_RENDER_COMMAND(command) m_object_manager.PushRenderCommand([&] {command;}, OpenGLCommandType::EOCT_ASYNC);
#define IOO_FLUSH_RENDER_COMMAND() m_object_manager.FlushRenderCommand();
	}
}

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

		protected:
			/*
			 * Register self to object manager
			 */
			virtual bool Register() = 0;

			OpenGLObjectManager& m_object_manager;
			OpenGLObjectHandle m_object_handle;
		};
	}
}

#pragma once
#include "IOpenGLResource.h"
#include "LevTokenDispatch.h"
#include "OpenGLObjectManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLTextureObject;
		class OpenGLObjectManager;

		typedef unsigned OpenGLObjectHandle;

		class IOpenGLObject : public IOpenGLResource
		{
		public:
			IOpenGLObject(OpenGLObjectManager& object_manager) 
				: IOpenGLResource(object_manager.GetResourceManager())
				, m_object_manager(object_manager)
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
	}
}

#pragma once

#include <string>
#include "Gl/glew.h"
#include "IOpenGLResource.h"
#include "OpenGLObjectManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLUniform : public IOpenGLResource
		{
		public:
			IOpenGLUniform(OpenGLObjectManager& object_manager)
				: IOpenGLResource(object_manager.GetResourceManager())
				, m_object_manager(object_manager)
			{
				
			}

			virtual bool Apply(GLuint program) = 0;
			virtual bool UnApply(GLuint program) = 0;

			virtual const std::string& GetUniformName() const = 0;

			virtual ~IOpenGLUniform() = default;

		protected:
			OpenGLObjectManager& m_object_manager;
		};
	}
}

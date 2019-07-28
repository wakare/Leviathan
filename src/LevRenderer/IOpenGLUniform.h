#pragma once
#include "Gl/glew.h"
#include "IOpenGLResource.h"
#include <string>

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLUniform : public IOpenGLResource
		{
		public:
			virtual bool Apply(GLuint program) = 0;
			virtual bool UnApply(GLuint program) = 0;

			virtual const std::string& GetUniformName() const = 0;

			virtual ~IOpenGLUniform() = default;
		};
	}
}

#pragma once

#include "IOpenGLRenderState.h"
#include "GL/glew.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRStatePointSize : public IOpenGLRenderState
		{
		public:
			OpenGLRStatePointSize();
			OpenGLRStatePointSize(GLuint point_size);

			OpenGLRStatePointSize* ToPointSize() override;

			OpenGLRenderStateType GetRenderStateType() const override;

			void SetPointSize(GLuint point_size);
			GLuint GetPointSize() const;

			void Apply() override;
			void UnApply() override;

		private:
			GLuint m_point_size;
		};
	}
}


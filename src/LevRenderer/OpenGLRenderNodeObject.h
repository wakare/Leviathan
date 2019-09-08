#pragma once
#include "LSPtr.h"
#include "GL/glew.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderStateManager;
		class OpenGLRenderEntry;
		class OpenGLFrameBufferObject;
		class OpenGLUniformManager;

		class OpenGLRenderNodeObject
		{
		public:
			OpenGLRenderNodeObject(LSPtr<OpenGLRenderEntry> object);
			bool Valid() const;
			unsigned GetID() const;

			void ApplyRenderState(OpenGLRenderStateManager& render_state_manager);
			void UnApplyRenderState(OpenGLRenderStateManager& render_state_manager);

			void ApplyUniform(OpenGLUniformManager& uniform_manager);
			void UnApplyUniform(OpenGLUniformManager& uniform_manager);

			void ApplyFrameBufferObject();
			void UnApplyFrameBufferObject();

			void Render(GLuint shader_program);

		private:
			LSPtr<OpenGLRenderEntry> m_object;
		};
	}
}

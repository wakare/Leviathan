#pragma once

#include <vector>
#include <gl/glew.h>
#include "LPtr.h"
#include "LevRAttrRenderObjectAttributeBinder.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevRAttrRenderStateManager;
	}

	namespace Renderer
	{
		class IOpenGLRenderState;
		class IOpenGLUniform;
		class OpenGLFrameBufferObject;

		class OpenGLRenderEntry
		{
		public:
			OpenGLRenderEntry(unsigned id, const Scene::LevRAttrRenderObjectAttributeBinder& attribute_binder);
			virtual ~OpenGLRenderEntry() = default;

			virtual bool Render(GLuint shaderProgram);

			unsigned GetID() const;

			const std::vector<LPtr<IOpenGLRenderState>>& GetRenderState() const;
			const std::vector<LPtr<IOpenGLUniform>>& GetUniforms() const;

			void SetRenderStateManager(const Scene::LevRAttrRenderStateManager& render_state);
			
			void SetFrameBufferObject(LPtr<OpenGLFrameBufferObject> frame_buffer);
			LPtr<OpenGLFrameBufferObject> GetFrameBufferObject();

			void AddRenderState(LPtr<IOpenGLRenderState> render_state);
			void AddUniform(LPtr<IOpenGLUniform> uniform);
			
		protected:
			OpenGLRenderEntry(unsigned id);
			virtual bool _init();

			const Scene::LevRAttrRenderObjectAttributeBinder m_attribute_binder;

			bool m_inited;

			LPtr<OpenGLFrameBufferObject> m_frame_buffer_object;
			std::vector<LPtr<IOpenGLUniform>> m_uniforms;
			std::vector<LPtr<IOpenGLRenderState>> m_render_states;

			GLuint m_VAO;
			GLuint m_VBO;
			GLuint m_IBO;

			const unsigned m_id;
			GLenum m_primitive_type;
		};
	}
}
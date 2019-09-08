#pragma once

#include <vector>
#include <gl/glew.h>
#include "LSPtr.h"
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

			const std::vector<LSPtr<IOpenGLRenderState>>& GetRenderState() const;
			const std::vector<LSPtr<IOpenGLUniform>>& GetUniforms() const;

			void SetRenderStateManager(const Scene::LevRAttrRenderStateManager& render_state);
			
			void SetFrameBufferObject(LSPtr<OpenGLFrameBufferObject> frame_buffer);
			LSPtr<OpenGLFrameBufferObject> GetFrameBufferObject();

			void AddRenderState(LSPtr<IOpenGLRenderState> render_state);
			void AddUniform(LSPtr<IOpenGLUniform> uniform);
			
		protected:
			OpenGLRenderEntry(unsigned id);
			virtual bool _init();

			const Scene::LevRAttrRenderObjectAttributeBinder m_attribute_binder;

			bool m_inited;

			LSPtr<OpenGLFrameBufferObject> m_frame_buffer_object;
			std::vector<LSPtr<IOpenGLUniform>> m_uniforms;
			std::vector<LSPtr<IOpenGLRenderState>> m_render_states;

			GLuint m_VAO;
			GLuint m_VBO;
			GLuint m_IBO;

			const unsigned m_id;
			GLenum m_primitive_type;
		};
	}
}
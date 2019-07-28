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
		class OpenGLNumericalUniform;
		class OpenGLRenderStateManager;

		class OpenGLRenderEntry
		{
		public:
			OpenGLRenderEntry(unsigned id, GLenum primitive_type, const Scene::LevRAttrRenderObjectAttributeBinder& attribute_binder);
			
			virtual bool PreRender(GLuint shaderProgram);
			virtual bool Render(GLuint shaderProgram);
			virtual bool PostRender(GLuint shaderProgram);

			unsigned GetID() const;

			void SetRenderStateManager(const Scene::LevRAttrRenderStateManager& render_state);
			void AddUniform(LPtr<OpenGLNumericalUniform> uniform);
			bool ApplyUniform(GLuint shaderProgram);
			
			void AddPreProcess(std::function<void()> fn);
			void AddPostProcess(std::function<void()> fn);

		protected:
			OpenGLRenderEntry(unsigned id);
			virtual bool _init();
			void _applyAllState();
			void _unapplyAllState();

			const Scene::LevRAttrRenderObjectAttributeBinder m_attribute_binder;

			bool m_inited;
			std::vector<LPtr<OpenGLNumericalUniform>> m_uniforms;
			LPtr<OpenGLRenderStateManager> m_render_state_manager;

			GLuint m_VAO;
			GLuint m_VBO;
			GLuint m_IBO;

			const unsigned m_id;
			GLenum m_primitive_type;

			std::vector<std::function<void()>> m_preprocess_fns;
			std::vector<std::function<void()>> m_postprocess_fns;
		};
	}
}
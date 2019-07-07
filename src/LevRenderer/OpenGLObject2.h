#pragma once

#include <vector>
#include <gl/glew.h>
#include "LPtr.h"
#include "LevRAttrRenderObjectAttributeBinder.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLUniform;

		class OpenGLObject2
		{
		public:
			OpenGLObject2(unsigned id, GLenum primitive_type, const Scene::LevRAttrRenderObjectAttributeBinder& attribute_binder);
			void AddUniform(LPtr<OpenGLUniform> uniform);
			virtual bool Render(GLuint shaderProgram);
			bool ApplyUniform(GLuint shaderProgram);
			unsigned GetID() const;
			void AddPreProcess(std::function<void()> fn);
			void AddPostProcess(std::function<void()> fn);

		protected:
			OpenGLObject2(unsigned id);
			virtual bool _init();

			const Scene::LevRAttrRenderObjectAttributeBinder m_attribute_binder;

			bool m_inited;
			std::vector<LPtr<OpenGLUniform>> m_uniforms;

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
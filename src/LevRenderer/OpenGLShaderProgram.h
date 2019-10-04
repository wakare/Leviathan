#pragma once

#include <gl/glew.h>
#include <map>
#include "LSPtr.h"
#include "IOpenGLObject.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevRAttrShaderProgram;
	}

	namespace Renderer
	{
		class OpenGLNumericalUniform;

		class OpenGLShaderProgram : public IOpenGLObject
		{
		public:
			OpenGLShaderProgram(OpenGLObjectManager& manager, const Scene::LevRAttrShaderProgram& shader_program);

			bool Init();
			bool SetGLUniformState();

			bool AddUniform(LSPtr<OpenGLNumericalUniform> pUniform);
			LSPtr<OpenGLNumericalUniform>& GetUniformByName(std::string uniformName);
			GLuint GetShaderProgram() const;
			unsigned GetID() const;

		private:
			bool _compileAll();
			bool _linkAll();
			bool _compileShader(const char* pczShaderSource, GLuint shaderProgram);

			GLuint m_VertexShader;
			GLuint m_FragmentShader;
			GLuint m_GeomShader;
			GLuint m_shaderProgram;
			GLboolean m_bInited;

			const Scene::LevRAttrShaderProgram& m_shader_program;
			std::map<std::string, LSPtr<OpenGLNumericalUniform>> m_pGLUniforms;
		};
	}
}

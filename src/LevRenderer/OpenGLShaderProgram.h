#pragma once

#include <gl/glew.h>
#include <map>
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLUniform;

		class OpenGLShaderProgram
		{
		public:
			OpenGLShaderProgram(const GLchar* const* pczVertexShader, const GLchar* const* pczFragmentShader, const GLchar* const* pczGeomShader);

			bool Init();
			bool SetGLUniformState();

			bool AddUniform(LPtr<OpenGLUniform> pUniform);
			LPtr<OpenGLUniform>& GetUniformByName(std::string uniformName);
			GLuint GetShaderProgram() const;

		private:
			bool _compileAll();
			bool _linkAll();
			bool _compileShader(const GLchar* const* pczShaderSource, GLuint shaderProgram);

			const GLchar* const* m_pczVertexShader;
			const GLchar* const* m_pczFragmentShader;
			const GLchar* const* m_pczGeomShader;

			GLuint m_VertexShader;
			GLuint m_FragmentShader;
			GLuint m_GeomShader;
			GLuint m_shaderProgram;
			GLboolean m_bInited;

			std::map<std::string, LPtr<OpenGLUniform>> m_pGLUniforms;
		};
	}
}
#pragma once
#include "GL/glew.h"
#include "GLUniform.h"
#include "LPtr.h"
#include <memory>
#include <map>

namespace Leviathan
{
	class GLShaderProgram
	{
	public:
		GLShaderProgram(const GLchar* const* pczVertexShader, const GLchar* const* pczFragmentShader, const GLchar* const* pczGeomShader) :
			m_pczVertexShader(pczVertexShader),
			m_pczFragmentShader(pczFragmentShader),
			m_pczGeomShader(pczGeomShader),
			m_bInited(false)
		{};

		bool Init();
		bool SetGLUniformState();

		bool AddUniform(LPtr<GLUniform> pUniform);
		LPtr<GLUniform>& GetUniformByName(std::string uniformName);
		GLuint GetShaderProgram() { return m_shaderProgram; };

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

		std::map<std::string, LPtr<GLUniform>> m_pGLUniforms;
	};
}
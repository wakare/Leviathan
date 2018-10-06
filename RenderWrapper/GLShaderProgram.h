#pragma once
#include "GL/glew.h"

class GLShaderProgram
{
public:
	GLShaderProgram(const GLchar* const* pczVertexShader, const GLchar* const* pczFragmentShader, const char* const* pczGeomShader = nullptr) :
		m_pczVertexShader(pczVertexShader), m_pczFragmentShader(pczFragmentShader), m_pczGeomShader(m_pczGeomShader)
	{};

	bool CompileAll();
	bool LinkAll();
	GLuint GetShaderProgram() { return m_shaderProgram; };

private:
	bool _compileShader(const GLchar* const* pczShaderSource, GLuint shaderProgram);

	const GLchar* const* m_pczVertexShader;
	const GLchar* const* m_pczFragmentShader;
	const GLchar* const* m_pczGeomShader;

	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	GLuint m_GeomShader;

	GLuint m_shaderProgram;
};
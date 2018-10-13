#pragma once
#include "GL/glew.h"
#include "GLUniform.h"
#include <memory>
#include <vector>

class GLUniform;

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
	
	bool AddUniform(std::shared_ptr<GLUniform> pUniform);
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

	std::vector<std::shared_ptr<GLUniform>> m_pGLUniforms;
};
#pragma once
#include <memory>
#include <vector>
#include "GLObject.h"
#include "GLShaderProgram.h"
#include <functional>

class GLPass
{
	typedef std::function<void(void)> Process;
public:
	GLPass(std::shared_ptr<GLShaderProgram> shaderProgram):
		m_pGLShaderProgram(shaderProgram), m_nPolygonMode(GL_FILL)
	{

	};

	std::vector<std::shared_ptr<GLObject>> GetGLObjects() { return m_GLObjects; };

	virtual bool Init() = 0;
	virtual void Render() = 0;

	void AddPreProcess(Process process) { m_PreRenderCallBacks.push_back(process); };
	void AddPostProcess(Process process) { m_PostRenderCallBacks.push_back(process); };

protected:
	std::shared_ptr<GLShaderProgram> m_pGLShaderProgram;
	std::vector<std::shared_ptr<GLObject>> m_GLObjects;

	std::vector<Process> m_PreRenderCallBacks;
	std::vector<Process> m_PostRenderCallBacks;

	GLuint m_nPolygonMode;
};
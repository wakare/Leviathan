#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "GLObject.h"
#include "GLShaderProgram.h"
#include "LPtr.h"

namespace Leviathan
{
	class GLPass
	{
		typedef std::function<void(void)> Process;
	public:
		GLPass(LPtr<GLShaderProgram> shaderProgram) :
			m_pGLShaderProgram(shaderProgram), m_nPolygonMode(GL_FILL)
		{

		};

		void AddGLObject(LPtr<GLObject> object) { m_GLObjects.push_back(object); }
		const std::vector<LPtr<GLObject>> GetGLObjects() { return m_GLObjects; };

		virtual bool Init() = 0;
		virtual void Render() = 0;

		void AddPreProcess(Process process) { m_PreRenderCallBacks.push_back(process); };
		void AddPostProcess(Process process) { m_PostRenderCallBacks.push_back(process); };
		void SetPolygonMode(GLuint nPolygonMode) { m_nPolygonMode = nPolygonMode; }

	protected:
		LPtr<GLShaderProgram> m_pGLShaderProgram;
		std::vector<LPtr<GLObject>> m_GLObjects;

		std::vector<Process> m_PreRenderCallBacks;
		std::vector<Process> m_PostRenderCallBacks;

		GLuint m_nPolygonMode;
	};
}
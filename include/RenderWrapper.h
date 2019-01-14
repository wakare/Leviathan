#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLPass.h"
#include "LPtr.h"

namespace Leviathan
{
	class RenderWrapper
	{
	public:
		RenderWrapper(GLFWwindow* pWindow) :m_pWindow(pWindow), m_bPreInited(false) {}
		void PreInit();
		void Render();
		bool AddGLPass(LPtr<GLPass> GLPass);
		bool DelGLPass(LPtr<GLPass> GLPass);
		bool Clear();
	private:

		GLboolean m_bPreInited;
		GLFWwindow* m_pWindow;
		std::vector<LPtr<GLPass>> m_GLPasses;
	};
}
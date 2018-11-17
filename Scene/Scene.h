#pragma once
#include "GLCamera.h"
#include "RenderWrapper.h"
#include "TriDObjectGLPass.h"
#include "TriDGLObject.h"
#include "GLShaderProgram.h"
#include "LPtr.h"

namespace Leviathan
{
	class Scene
	{
	public:
		Scene(GLFWwindow* pRenderWindow, int width, int height);

		virtual void Update();

		LPtr<GLCamera> m_pCamera;
	private:
		std::string _getShaderSource(const char* pczShaderSourcePath);

		GLFWwindow* m_pGLFWWindow;

		LPtr<RenderWrapper> m_pRenderWarpper;
		LPtr<TriDObjectGLPass> m_pMeshPass;
		LPtr<GLShaderProgram> m_pShaderProgram;
	};
}
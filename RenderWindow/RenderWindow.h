#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <memory>
#include "WindowCallBack.h"
#include "Scene.h"
#include "CFileImportFactory.h"
#include "LPtr.h"

namespace Leviathan
{
	class RenderWindow : public EventListener
	{
	public:
		RenderWindow(LPtr<EventSystem> pEventSystem, GLint width = 800, GLint height = 600, GLchar* pTitle = "RenderWindow");
		bool CreateRenderWindow();
		void Run();

		void Accept(Event event);

		GLFWwindow* GetGLFWWindow() { return m_pWindow; };
		GLint GetWidth() { return m_width; };
		GLint GetHeight() { return m_height; };

	private:
		void _updateCameraTransform(Event& event);
		void _setWindowProcess();
		bool _glewInit();

		GLint m_width;
		GLint m_height;
		GLchar* m_pWindowTitle;

		GLFWwindow* m_pWindow;
		LPtr<Scene> m_pScene;
		LPtr<EventSystem> m_pEventSystem;
	};
}
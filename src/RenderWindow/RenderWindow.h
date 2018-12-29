#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <memory>
#include "LPtr.h"
#include "EventListener.h"

namespace Leviathan
{
	class EventSystem;
	class Event;
	class CCommonScene;
	class IFileImportFactory;

	class RenderWindow : public EventListener
	{
	public:
		RenderWindow(LPtr<EventSystem> pEventSystem, GLint width = 1920, GLint height = 1200, GLchar* pTitle = "RenderWindow");
		bool CreateRenderWindow();
		void Run();

		void Accept(Event& event);

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
		LPtr<CCommonScene> m_pScene;
		LPtr<EventSystem> m_pEventSystem;
		LPtr<IFileImportFactory> m_pFileImporter;
	};
}
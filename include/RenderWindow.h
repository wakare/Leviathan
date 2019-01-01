#pragma once

#include <GL\glew.h>
#include <memory>
#include "LPtr.h"
#include "EventListener.h"

struct GLFWwindow;

namespace Leviathan
{
	class EventSystem;
	class Event;
	class CommonScene;
	class IFileImportFactory;
	
	class RenderWindow : public EventListener
	{
	public:
		RenderWindow(LPtr<EventSystem> pEventSystem, GLint width = 1920, GLint height = 1200, GLchar* pTitle = "Leviathan");
		bool CreateRenderWindow();
		void Run();

		void Accept(Event& event);

		GLFWwindow* GetGLFWWindow() { return m_pWindow; };
		GLint GetWidth() { return m_width; };
		GLint GetHeight() { return m_height; };
		LPtr<CommonScene> GetScene() { if (m_pScene == nullptr) CreateRenderWindow(); return m_pScene; }

	private:
		void _updateCameraTransform(Event& event);
		void _setWindowProcess();
		bool _glewInit();

		GLint m_width;
		GLint m_height;
		GLchar* m_pWindowTitle;

		GLFWwindow* m_pWindow;
		LPtr<CommonScene> m_pScene;
		LPtr<EventSystem> m_pEventSystem;
		LPtr<IFileImportFactory> m_pFileImporter;
	};
}
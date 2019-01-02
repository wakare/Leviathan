#pragma once

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
		RenderWindow(LPtr<EventSystem> pEventSystem, int width = 1920, int height = 1200, char* pTitle = (char*)"Leviathan");
		bool CreateRenderWindow();
		void Run();

		void Accept(Event& event);

		GLFWwindow* GetGLFWWindow() { return m_pWindow; };
		int GetWidth() { return m_width; };
		int GetHeight() { return m_height; };
		LPtr<CommonScene> GetScene() { if (m_pScene == nullptr) CreateRenderWindow(); return m_pScene; }

	private:
		void _updateCameraTransform(Event& event);
		void _setWindowProcess();
		bool _glewInit();

		int m_width;
		int m_height;
		char* m_pWindowTitle;

		GLFWwindow* m_pWindow;
		LPtr<CommonScene> m_pScene;
		LPtr<EventSystem> m_pEventSystem;
		LPtr<IFileImportFactory> m_pFileImporter;
	};
}
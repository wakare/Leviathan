#pragma once

#include <gl/glew.h>
#include <glfw/glfw3.h>
#include "LPtr.h"
#include "EventListener.h"

namespace Leviathan
{
	class Event;
	class EventSystem;

	class LevRenderWindow : public EventListener
	{
		public:
			LevRenderWindow(LPtr<EventSystem> pEventSystem, int width = 1080, int height = 720, char* pTitle = (char*)"Leviathan");
			~LevRenderWindow();

			bool Create(int width, int height, int hParent = NULL);
			void Run();
			void Update();
			void Stop();
			void Accept(Event& event);

			int GetWidth();
			int GetHeight();
			int GetWindowHandle() const;
			GLFWwindow* GetGLFWWindow();

		private:
			void _setWindowProcess();
			bool _glewInit();
			void _handleInput(Event& event);
			bool _handleResize(Event& event);

			int m_width;
			int m_height;
			char* m_pWindowTitle;
			bool m_bRunning;

			GLFWwindow* m_pWindow;
			LPtr<EventSystem> m_pEventSystem;
	};
}
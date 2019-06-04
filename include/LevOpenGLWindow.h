#pragma once

#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "ILevWindow.h"
#include "LPtr.h"

namespace Leviathan
{
	class LevOpenGLWindow : public ILevWindow
	{
	public:
		LevOpenGLWindow(int width = 1080, int height = 720, char* pTitle = (char*)"Leviathan");

		bool Create(int width, int height, int hParent = 0);
		void Run();
		void Update();
		void SetStop();
		bool Stoped();
		void Accept(Event& event);

		int GetWidth() const;
		int GetHeight() const;
		int GetWindowHandle() const;
		void SwapBuffer();

	private:
		void _setWindowProcess();
		bool _glewInit();
		void _handleInput(Event& event);
		bool _handleResize(Event& event);

		int m_width;
		int m_height;
		char* m_pWindowTitle;
		bool m_bRunning;
		volatile bool m_bStopped;

		GLFWwindow* m_pWindow;
	};
}
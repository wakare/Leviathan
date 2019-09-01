#pragma once

#include <GL/glew.h>
#include <glfw/glfw3.h>

#include "ILevWindow.h"
#include "LevCoreExport.h"

namespace Leviathan
{
	class LEV_CORE_API LevOpenGLWindow : public ILevWindow
	{
	public:
		LevOpenGLWindow(int width = 1080, int height = 720, char* pTitle = (char*)"Leviathan");

		bool Create(int width, int height, int hParent = 0) override;
		void Run() override;
		void Update() override;
		void SetStop() override;
		bool HasStoped() override;
		void Accept(Event& event) override;

		int GetWidth() const override;
		int GetHeight() const override;
		int GetWindowHandle() const override;

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
#pragma once

#include <memory>
#include "LPtr.h"
#include "EventListener.h"
#include "IScene.h"

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
		RenderWindow(LPtr<EventSystem> pEventSystem, IScene::ESceneType sceneType = IScene::EST_POINTCLOUD, int width = 1080, int height = 720, char* pTitle = (char*)"Leviathan");
		~RenderWindow();

		bool CreateRenderWindow();
		void Run();
		void SyncStop();
		void AsyncStop();
		void Accept(Event& event);

		GLFWwindow* GetGLFWWindow() { return m_pWindow; };
		int GetWidth() { return m_width; };
		int GetHeight() { return m_height; };
		LPtr<CommonScene> GetScene() { if (m_pScene == nullptr) CreateRenderWindow(); return m_pScene; }

	private:
		void _handleInput(Event& event);
		bool _handleCameraTransform(Event& event);
		bool _handlePick(Event& event);
		void _setWindowProcess();
		bool _glewInit();

		int m_width;
		int m_height;
		char* m_pWindowTitle;
		bool m_bRunning;

		GLFWwindow* m_pWindow;
		IScene::ESceneType m_sceneType;
		LPtr<CommonScene> m_pScene;
		LPtr<EventSystem> m_pEventSystem;
		LPtr<IFileImportFactory> m_pFileImporter;
	};
}
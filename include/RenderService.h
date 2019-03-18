#pragma once

#include "LPtr.h"
#include "IScene.h"

namespace Leviathan
{
	class EventSystem;
	class EventListener;
	class RenderWindow;
	class CommonScene;
	class View;

	class RenderService
	{
	public:
		static RenderService* Instance();

		LPtr<CommonScene> GetScene();

		bool Init(int width, int height, int handle);
		void Run();
		void SyncStop();
		void AsyncStop();

		bool AddEventListener(EventType eventType, LPtr<EventListener> listener);
		bool _attachNativeWin32Window(int width, int height, int handle);
		int GetWindowHandle() const;
	private:
		RenderService();

		static RenderService* g_pInstance;
		static IScene::ESceneType m_sceneType;

		std::shared_ptr<View> m_pView;
	}; 
}
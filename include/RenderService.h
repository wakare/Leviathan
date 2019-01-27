#pragma once

#include "LPtr.h"
#include "IScene.h"

namespace Leviathan
{
	class EventSystem;
	class EventListener;
	class RenderWindow;
	class CommonScene;

	class RenderService
	{
	public:
		static RenderService* Instance();
		static void SetSceneType(IScene::ESceneType type);

		bool SetCurrentScene(LPtr<CommonScene> pScene);
		LPtr<CommonScene> GetScene();
		bool Init();
		void Run();
		void SyncStop();
		bool AddEventListener(EventType eventType, LPtr<EventListener> listener);

	private:
		RenderService();
		static RenderService* g_pInstance;
		static IScene::ESceneType m_sceneType;

		LPtr<EventSystem> m_pEventSystem;
		LPtr<RenderWindow> m_pRenderWindow;
		LPtr<CommonScene> m_pScene;
	}; 
}
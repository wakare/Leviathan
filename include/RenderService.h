#pragma once

#include "LPtr.h"
#include "IScene.h"
#include "Singleton.h"

namespace Leviathan
{
	class EventSystem;
	class EventListener;
	class RenderWindow;
	class CommonScene;
	class View;

	class RenderService
	{
		DECLARE_SELF_TO_SINGLETON(RenderService)
	public:
		static RenderService& Instance();

		LPtr<CommonScene> GetScene();

		bool Init(int width, int height, int handle, IScene::ESceneType scene_type = IScene::EST_TRID);
		void Run();
		void SyncStop();
		void AsyncStop();

		bool AddEventListener(EventType eventType, LPtr<EventListener> listener);
		bool _attachNativeWin32Window(int width, int height, int handle);
		int GetWindowHandle() const;

	private:
		RenderService();
		IScene::ESceneType m_sceneType;
		std::shared_ptr<View> m_pView;
	}; 
}
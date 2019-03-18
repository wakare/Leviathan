#pragma once
#include "IScene.h"
#include "LPtr.h"

namespace Leviathan
{
	class EventSystem;
	class EventListener;
	class RenderWindow;
	class CommonScene;

	class View
	{
	public:
		View(IScene::ESceneType type = IScene::EST_TRID);
		LPtr<CommonScene> GetScene();

		bool Init(int width, int height, int handle);
		void Run();
		void SyncStop();
		void AsyncStop();

		int GetWindowHandle() const;
		bool AddEventListener(EventType eventType, LPtr<EventListener> listener);
		bool AttachNativeWin32Window(int width, int height, int handle);

	private:
		IScene::ESceneType m_sceneType;

		LPtr<EventSystem> m_pEventSystem;
		LPtr<RenderWindow> m_pRenderWindow;
		LPtr<CommonScene> m_pScene;
	};
}
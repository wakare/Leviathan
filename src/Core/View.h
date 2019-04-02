#pragma once
#include "IScene.h"
#include "LPtr.h"
#include "ViewData.h"

namespace Leviathan
{
	class EventSystem;
	class EventListener;
	class RenderWindow;
	class CommonScene;
	class Presenter;

	class View
	{
	public:
		View(IScene::ESceneType type = IScene::EST_TRID);
		LPtr<CommonScene> GetScene();

		bool Init(int width, int height, int handle);
		void Update();
		void SyncStop();
		void AsyncStop();

		int GetWindowHandle() const;
		bool AddEventListener(EventType eventType, LPtr<EventListener> listener);
		
	private:
		bool _attachNativeWin32Window(int width, int height, int handle);

		std::unique_ptr<ViewData> m_pData;
	};
}
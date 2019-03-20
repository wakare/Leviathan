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
		View(Presenter& presenter, IScene::ESceneType type = IScene::EST_TRID);
		LPtr<CommonScene> GetScene();

		bool Init(int width, int height, int handle);
		void Run();
		void SyncStop();
		void AsyncStop();

		int GetWindowHandle() const;
		bool AddEventListener(EventType eventType, LPtr<EventListener> listener);
		bool AttachNativeWin32Window(int width, int height, int handle);

	private:
		Presenter& presenter;
		std::unique_ptr<ViewData> m_pData;
	};
}
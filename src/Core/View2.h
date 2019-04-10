#pragma once

#include <memory>
#include "GlobalDef.h"
#include "LPtr.h"
#include "ViewData2.h"

namespace Leviathan
{
	class EventListener;
	class LevScene;

	class View2
	{
	public:
		View2(LevSceneType type = ELST_3D_SCENE);

		bool Init(int width, int height, int handle);
		void Update();
		void SyncStop();
		void AsyncStop();

		int GetWindowHandle() const;
		bool AddEventListener(EventType eventType, LPtr<EventListener> listener);

	private:
		std::unique_ptr<ViewData2> m_pData;
	};
}
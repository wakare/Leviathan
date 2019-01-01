#pragma once
#include "LPtr.h"

namespace Leviathan
{
	class EventSystem;
	class RenderWindow;
	class CommonScene;

	class RenderService
	{
	public:
		static RenderService* Instance();
		LPtr<CommonScene> GetScene();
		
		void Run();

	private:
		RenderService();
		static RenderService* g_pInstance;

		LPtr<EventSystem> pEventSystem;
		LPtr<RenderWindow> pRenderWindow;
		LPtr<CommonScene> pScene;
	};
}
#include "RenderService.h"
#include <memory>
#include <iostream>
#include "RenderWindow.h"
#include "EventSystem.h"
#include "CCommonScene.h"
#include <mutex>

namespace Leviathan
{
	RenderService* RenderService::g_pInstance = nullptr;

	RenderService::RenderService():
		pScene(nullptr)
	{
		pEventSystem = new EventSystem();
		pRenderWindow = new RenderWindow(pEventSystem);
		pEventSystem->AddEventListener(Event::EventType::INPUT_EVENT, TryCast<RenderWindow, EventListener>(pRenderWindow));
	}

	RenderService * RenderService::Instance()
	{
		static std::once_flag _flag;
		if (g_pInstance == nullptr)
		{
			std::call_once(_flag, []() {g_pInstance = new RenderService(); });
		}

		return g_pInstance;
	}

	Leviathan::LPtr<Leviathan::CommonScene> RenderService::GetScene()
	{
		if (pScene == nullptr)
		{
			pScene = pRenderWindow->GetScene();
			if (pScene == nullptr)
			{
				throw "exception";
			}
		}

		return pScene;
	}

	void RenderService::Run()
	{
		pRenderWindow->Run();
	}

	void RenderService::AsyncStop()
	{
		pRenderWindow->Stop();
	}
}
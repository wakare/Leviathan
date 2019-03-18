#include "View.h"

#include <mutex>
#include <memory>
#include <iostream>

#include "RenderService.h"
#include "RenderWindow.h"
#include "EventSystem.h"
#include "CommonScene.h"
#include "GlobalDef.h"

namespace Leviathan
{
	View::View(IScene::ESceneType type /*= IScene::EST_TRID*/):
		m_pScene(nullptr),
		m_sceneType(type)
	{
		m_pEventSystem = new EventSystem();
		m_pRenderWindow = new RenderWindow(m_pEventSystem, m_sceneType);

		auto eventListener = TryCast<RenderWindow, EventListener>(m_pRenderWindow);
		m_pEventSystem->AddEventListener(EventType::INPUT_EVENT, eventListener);
	}

	Leviathan::LPtr<Leviathan::CommonScene> View::GetScene()
	{
		if (m_pScene == nullptr)
		{
			m_pScene = m_pRenderWindow->GetScene();
			if (m_pScene == nullptr)
			{
				throw "exception";
			}
		}

		return m_pScene;
	}

	bool View::Init(int width, int height, int handle)
	{
		EXIT_IF_FALSE(AttachNativeWin32Window(width, height, handle));
		EXIT_IF_FALSE(m_pRenderWindow->GetScene());
		return true;
	}

	void View::Run()
	{
		m_pRenderWindow->Run();
	}

	void View::SyncStop()
	{
		m_pRenderWindow->SyncStop();
	}

	void View::AsyncStop()
	{
		m_pRenderWindow->AsyncStop();
	}

	bool View::AddEventListener(EventType eventType, LPtr<EventListener> listener)
	{
		EXIT_IF_FALSE(listener);
		m_pEventSystem->AddEventListener(eventType, listener);
		return true;
	}

	int View::GetWindowHandle() const
	{
		return m_pRenderWindow->GetWindowHandle();
	}

	bool View::AttachNativeWin32Window(int width, int height, int handle)
	{
		return m_pRenderWindow->CreateRenderWindow(width, height, handle);
	}

}
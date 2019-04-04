#include "ViewData.h"
#include "EventSystem.h"
#include "RenderWindow.h"
#include "CommonScene.h"

namespace Leviathan
{
	ViewData::ViewData(IScene::ESceneType type):
		m_sceneType(type)
	{
		m_pEventSystem = new EventSystem();
		m_pRenderWindow = new RenderWindow(m_pEventSystem, m_sceneType);

		auto eventListener = TryCast<RenderWindow, EventListener>(m_pRenderWindow);
		m_pEventSystem->AddEventListener(EventType::INPUT_EVENT, eventListener);
	}

	EventSystem & ViewData::GetEventSystem()
	{
		return *m_pEventSystem;
	}

	RenderWindow & ViewData::GetRenderWindow()
	{
		return *m_pRenderWindow;
	}

	CommonScene & ViewData::GetScene()
	{
		return *m_pScene;
	}

}

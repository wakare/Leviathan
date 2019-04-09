#include "View2.h"
#include "LevScene.h"
#include "ViewData2.h"
#include "EventSystem.h"
#include "LevRenderWindow.h"
#include "IRenderer.h"
#include "LevSceneEventListener.h"

namespace Leviathan
{
	View2::View2(LevSceneType type /*= ELST_3D_SCENE*/) :
		m_pData(nullptr)
	{
		m_pData.reset(new ViewData2(ELRT_OPENGL));

		LPtr<EventListener> eventListener = TryCast<Scene::LevSceneEventListener, EventListener>(m_pData->GetScene().GetEventListener());
		m_pData->GetEventSystem().AddEventListener(INPUT_EVENT, eventListener);
	}

	bool View2::Init(int width, int height, int handle)
	{
		EXIT_IF_FALSE(m_pData->GetRenderWindow().Create(width, height, handle));
		return true;
	}

	void View2::Update()
	{
		m_pData->GetEventSystem().DispatchEvent();
		m_pData->GetRenderWindow().Update();
		m_pData->GetScene().Update();
		m_pData->GetRenderer().SetInputData(m_pData->GetScene().GetSceneData());
		m_pData->GetRenderer().Update();
	}

	void View2::SyncStop()
	{
		m_pData->GetRenderWindow().Stop();
	}

	void View2::AsyncStop()
	{
		m_pData->GetRenderWindow().Stop();
	}

	bool View2::AddEventListener(EventType eventType, LPtr<EventListener> listener)
	{
		EXIT_IF_FALSE(listener);
		m_pData->GetEventSystem().AddEventListener(eventType, listener);
		return true;
	}

	int View2::GetWindowHandle() const
	{
		return m_pData->GetRenderWindow().GetWindowHandle();
	}
}
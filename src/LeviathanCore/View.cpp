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
	View::View(Presenter& presenter, IScene::ESceneType type /*= IScene::EST_TRID*/):
		m_presenter(presenter),
		m_pData(nullptr),
		m_pStateMgr(nullptr)
	{
		m_pData.reset(new ViewData(type));
		m_pStateMgr.reset(new ViewStateMgr(*m_pData));
		m_pStateMgr->SetViewStateType(EVS_UNINITED);
	}

	Leviathan::LPtr<Leviathan::CommonScene> View::GetScene()
	{
		return m_pData->GetRenderWindow().GetScene();
	}

	bool View::Init(int width, int height, int handle)
	{
		EXIT_IF_FALSE(m_pStateMgr->getViewStateType() == EVS_UNINITED);
		m_pStateMgr->SetViewStateType(EVS_INITING);
		EXIT_IF_FALSE(_attachNativeWin32Window(width, height, handle));
		m_pStateMgr->SetViewStateType(EVS_INITED);

		return true;
	}

	void View::Run()
	{
		if (m_pStateMgr->getViewStateType() != EVS_INITED) {
			return;
		}

		m_pStateMgr->SetViewStateType(EVS_RUNNING);
		m_pData->GetRenderWindow().Update();
	}

	void View::SyncStop()
	{
		if (m_pStateMgr->getViewStateType() != EVS_RUNNING) {
			return;
		}

		m_pStateMgr->SetViewStateType(EVS_STOPPING);
		m_pData->GetRenderWindow().SyncStop();
		m_pStateMgr->SetViewStateType(EVS_STOPPED);
	}

	void View::AsyncStop()
	{
		m_pStateMgr->SetViewStateType(EVS_STOPPING);
		m_pData->GetRenderWindow().AsyncStop();
	}

	bool View::AddEventListener(EventType eventType, LPtr<EventListener> listener)
	{
		EXIT_IF_FALSE(listener);
		m_pData->GetEventSystem().AddEventListener(eventType, listener);
		return true;
	}

	int View::GetWindowHandle() const
	{
		return m_pData->GetRenderWindow().GetWindowHandle();
	}

	bool View::_attachNativeWin32Window(int width, int height, int handle)
	{
		return m_pData->GetRenderWindow().CreateRenderWindow(width, height, handle);
	}

}
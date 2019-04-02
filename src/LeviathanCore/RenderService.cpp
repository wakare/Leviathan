#include <mutex>
#include <memory>
#include <iostream>
#include "RenderService.h"
#include "RenderWindow.h"
#include "EventSystem.h"
#include "CommonScene.h"
#include "GlobalDef.h"
#include "View.h"
#include "Presenter.h"

namespace Leviathan
{	
	RenderService::RenderService():
		m_pView(new View(Presenter::Instance()))
	{
	}

	RenderService& RenderService::Instance()
	{
		return Singleton<RenderService>::Instance();
	}

	Leviathan::LPtr<Leviathan::CommonScene> RenderService::GetScene()
	{
		return m_pView->GetScene();
	}

	bool RenderService::Init(int width, int height, int handle, IScene::ESceneType scene_type /*= IScene::EST_TRID*/)
	{
		EXIT_IF_FALSE(m_pView->Init(width, height, handle));
		return true;
	}

	void RenderService::Run()
	{
		m_pView->Update();
	}

	void RenderService::SyncStop()
	{
		m_pView->SyncStop();
	}

	void RenderService::AsyncStop()
	{
		m_pView->AsyncStop();
	}

	bool RenderService::AddEventListener(EventType eventType, LPtr<EventListener> listener)
	{
		EXIT_IF_FALSE(listener);
		m_pView->AddEventListener(eventType, listener);
		return true;
	}

	int RenderService::GetWindowHandle() const
	{
		return m_pView->GetWindowHandle();
	}

}
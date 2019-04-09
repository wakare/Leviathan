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
		m_pData(nullptr)
	{
		m_pData.reset(new ViewData(type));
	}

	Leviathan::LPtr<Leviathan::CommonScene> View::GetScene()
	{
		return m_pData->GetRenderWindow().GetScene();
	}

	bool View::Init(int width, int height, int handle)
	{
		EXIT_IF_FALSE(_attachNativeWin32Window(width, height, handle)); 

		return true;
	}

	void View::Update()
	{
		m_pData->GetRenderWindow().Update();
	}

	void View::SyncStop()
	{
		m_pData->GetRenderWindow().SyncStop();
	}

	void View::AsyncStop()
	{
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
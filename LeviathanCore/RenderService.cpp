#include <mutex>
#include <memory>
#include <iostream>
#include "RenderService.h"
#include "RenderWindow.h"
#include "EventSystem.h"
#include "CommonScene.h"
#include "GlobalDef.h"
#include "View.h"

namespace Leviathan
{
	RenderService* RenderService::g_pInstance = nullptr;
	
	RenderService::RenderService():
		m_pView(new View())
	{
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

	bool RenderService::_attachNativeWin32Window(int width, int height, int handle)
	{
		return m_pView->AttachNativeWin32Window(width, height, handle);
	}

	Leviathan::LPtr<Leviathan::CommonScene> RenderService::GetScene()
	{
		return m_pView->GetScene();
	}

	bool RenderService::Init(int width, int height, int handle)
{
		EXIT_IF_FALSE(_attachNativeWin32Window(width, height, handle));
		EXIT_IF_FALSE(GetScene());
		return true;
	}

	void RenderService::Run()
	{
		m_pView->Run();
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
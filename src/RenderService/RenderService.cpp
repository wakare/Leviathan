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
	RenderService* RenderService::g_pInstance = nullptr;
	IScene::ESceneType RenderService::m_sceneType = IScene::EST_POINTCLOUD;
	
	RenderService::RenderService():
		m_pScene(nullptr)
	{
		m_pEventSystem = new EventSystem();
		m_pRenderWindow = new RenderWindow(m_pEventSystem, m_sceneType);
		m_pEventSystem->AddEventListener(EventType::INPUT_EVENT, TryCast<RenderWindow, EventListener>(m_pRenderWindow));
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

	void RenderService::SetSceneType(IScene::ESceneType type)
	{
		m_sceneType = type;
	}

	bool RenderService::SetCurrentScene(LPtr<CommonScene> pScene)
	{
		m_pScene = pScene;
		return true;
	}

	Leviathan::LPtr<Leviathan::CommonScene> RenderService::GetScene()
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

	bool RenderService::Init()
	{
		EXIT_IF_FALSE(m_pRenderWindow->GetScene());
		return true;
	}

	void RenderService::Run()
	{
		m_pRenderWindow->Run();
	}

	void RenderService::SyncStop()
	{
		m_pRenderWindow->SyncStop();
	}

	void RenderService::AsyncStop()
	{
		m_pRenderWindow->AsyncStop();
	}

	bool RenderService::AddEventListener(EventType eventType, LPtr<EventListener> listener)
	{
		EXIT_IF_FALSE(listener);
		m_pEventSystem->AddEventListener(eventType, listener);
		return true;
	}

}
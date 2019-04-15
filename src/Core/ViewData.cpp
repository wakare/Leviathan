#include "ViewData.h"
#include "OpenGLRenderer.h"
#include "IRenderer.h"
#include "LevRenderWindow.h"
#include "EventSystem.h"
#include "LevScene.h"

namespace Leviathan
{
	ViewData::ViewData(LevRendererType render_type):
		m_renderType(render_type)
	{
		m_pEventSystem.Reset(new EventSystem);
		m_pWindow.Reset(new LevRenderWindow(m_pEventSystem.Get()));
		m_pEventSystem->AddEventListener(INPUT_EVENT, TryCast<LevRenderWindow, EventListener>(m_pWindow));

		m_pScene.Reset(new Scene::LevScene);
		bool inited = m_pScene->Init(ELST_3D_SCENE);
		LEV_ASSERT(inited);
	}

	Leviathan::EventSystem& ViewData::GetEventSystem()
	{
		return *m_pEventSystem;
	}

	LevRenderWindow & ViewData::GetRenderWindow()
	{
		return *m_pWindow;
	}

	Scene::LevScene & ViewData::GetScene()
	{
		return *m_pScene;
	}

	Renderer::IRenderer & ViewData::GetRenderer()
	{
		return *m_pRenderer;
	}

	bool ViewData::InitRenderer()
	{
		switch (m_renderType)
		{
		case ELRT_OPENGL:
			m_pRenderer.Reset(new Renderer::OpenGLRenderer(m_pWindow->GetGLFWWindow()));
			break;

		default:
			return false;
		}

		return true;
	}

}
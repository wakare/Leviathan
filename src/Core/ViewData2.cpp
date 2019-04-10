#include "ViewData2.h"
#include "OpenGLRenderer.h"
#include "IRenderer.h"
#include "LevRenderWindow.h"
#include "EventSystem.h"
#include "LevScene.h"

namespace Leviathan
{
	ViewData2::ViewData2(LevRendererType render_type):
		m_renderType(render_type)
	{
		m_pEventSystem.Reset(new EventSystem);
		m_pWindow.Reset(new LevRenderWindow(m_pEventSystem.Get()));
		
		m_pScene.Reset(new Scene::LevScene);
		LEV_ASSERT(m_pScene->Init(ELST_3D_SCENE));
	}

	Leviathan::EventSystem& ViewData2::GetEventSystem()
	{
		return *m_pEventSystem;
	}

	LevRenderWindow & ViewData2::GetRenderWindow()
	{
		return *m_pWindow;
	}

	Scene::LevScene & ViewData2::GetScene()
	{
		return *m_pScene;
	}

	Renderer::IRenderer & ViewData2::GetRenderer()
	{
		return *m_pRenderer;
	}

	bool ViewData2::InitRenderer()
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
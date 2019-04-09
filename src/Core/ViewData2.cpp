#include "ViewData2.h"
#include "OpenGLRenderer.h"
#include "IRenderer.h"
#include "LevRenderWindow.h"
#include "EventSystem.h"
#include "LevScene.h"

namespace Leviathan
{
	ViewData2::ViewData2(LevRendererType render_type)
	{
		m_pEventSystem.Reset(new EventSystem);
		m_pWindow.Reset(new LevRenderWindow(m_pEventSystem.Get()));

		switch (render_type)
		{
		case ELRT_OPENGL:
			m_pRenderer.Reset(new Renderer::OpenGLRenderer(m_pWindow->GetGLFWWindow()));
			break;
		}

		m_pScene.Reset(new Scene::LevScene);
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

}
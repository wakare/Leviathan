#include "ViewData.h"
#include "OpenGLRenderer.h"
#include "IRenderer.h"
#include "EventSystem.h"
#include "LevScene.h"
#include "LevWindowFactory.h"
#include "LevOpenGLWindow.h"

namespace Leviathan
{
	ViewData::ViewData(LevRendererType render_type):
		m_renderType(render_type)
	{		
		m_pLevWindowFactory.Reset(new LevWindowFactory);
		auto created = m_pLevWindowFactory->Create(LevWindowType::ELWT_OPENGL, m_pWindow);
		LEV_ASSERT(created);

		m_pEventSystem = TryCast<ILevWindow, EventSystem>(m_pWindow);
		m_pScene.Reset(new Scene::LevScene);
		bool inited = m_pScene->Init(ELST_3D_SCENE);
		LEV_ASSERT(inited);
	}

	Leviathan::EventSystem& ViewData::GetEventSystem()
	{
		return *m_pEventSystem;
	}

	Leviathan::ILevWindow& ViewData::GetRenderWindow()
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
		{
			LevOpenGLWindow* pOpenGLWindow = dynamic_cast<LevOpenGLWindow*>(m_pWindow.Get());
			EXIT_IF_FALSE(pOpenGLWindow);

			m_pRenderer.Reset(new Renderer::OpenGLRenderer(*pOpenGLWindow));
			break;
		}

		default:
			return false;
		}

		return true;
	}

}
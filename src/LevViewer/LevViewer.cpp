#include "LevViewer.h"
#include "LevScene.h"
#include "LevWindowFactory.h"
#include "ILevWindow.h"
#include "OpenGLRenderer.h"
#include "EventSystem.h"
#include "LevOpenGLWindow.h"
#include "LevSceneEventListener.h"

namespace Leviathan
{
	namespace Viewer
	{
		LevViewer::LevViewer()
			: m_event_system(new EventSystem)
		{
			
		}

		bool LevViewer::CreateRenderWindow(int width, int height, unsigned handle)
		{
			// Create window 
			EXIT_IF_FALSE(!m_window);
			EXIT_IF_FALSE(LevWindowFactory::Create(ELWT_OPENGL, m_window));
			EXIT_IF_FALSE(m_window->Create(width, height, handle));

			// Reset render
			LevOpenGLWindow* openGL_window = dynamic_cast<LevOpenGLWindow*>(m_window.Get());
			//LPtr<LevOpenGLWindow> openGL_window = TryCast<ILevWindow, LevOpenGLWindow>(m_window);
			EXIT_IF_FALSE(openGL_window);

			m_renderer.Reset(new Renderer::OpenGLRenderer(*openGL_window));
			return true;
		}

		bool LevViewer::SetCurrentScene(LPtr<Scene::LevScene> current_scene)
		{
			EXIT_IF_FALSE(current_scene);
			m_current_scene = current_scene;

			LPtr<EventListener> eventListener = TryCast<Scene::LevSceneEventListener, EventListener>(current_scene->GetEventListener());
			LEV_ASSERT(eventListener);
			m_event_system->AddEventListener(INPUT_EVENT, eventListener.Get());

			return true;
		}

		void LevViewer::TickFrame()
		{
			m_event_system->DispatchEvent();
			m_window->Update();
			m_current_scene->UpdateTimer();

			if (m_current_scene->HasModified())
			{
				m_current_scene->SetNodeModified();
				m_current_scene->UpdateWorldTransform();
				m_renderer->SetInputData(m_current_scene->GetSceneData());

				// Scene update must be later than render update, because it will overwrite modified state info.
				m_current_scene->UpdateNodeState();

				m_current_scene->ResetModified();
			}

			m_renderer->Update();
		}

		void LevViewer::SetStop()
		{
			m_window->SetStop();
		}

		bool LevViewer::HasStoped()
		{
			return m_window->Stoped();
		}

		const ILevWindow & LevViewer::GetRenderWindow() const
		{
			return *m_window;
		}

	}
}
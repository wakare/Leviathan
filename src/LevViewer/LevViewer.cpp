#include "LevViewer.h"
#include "LevScene.h"
#include "LevWindowFactory.h"
#include "ILevWindow.h"
#include "OpenGLRenderBackend.h"
#include "EventSystem.h"
#include "LevOpenGLWindow.h"
#include "LevSceneEventListener.h"

namespace Leviathan
{
	namespace Viewer
	{
		LevViewer::LevViewer()
			: m_event_system(nullptr)
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
			EXIT_IF_FALSE(openGL_window);

			// Set event system
			m_event_system = TryCast<ILevWindow, EventSystem>(m_window);
			LEV_ASSERT(m_event_system);

			m_renderer.Reset(new Renderer::OpenGLRenderBackend(*openGL_window));
			return true;
		}

		bool LevViewer::ResizeWindow(int width, int height)
		{
			if (!m_window)
			{
				return false;
			}

			return m_window->Resize(width, height);
		}

		bool LevViewer::SetCurrentScene(LSPtr<Scene::LevScene> current_scene)
		{
			EXIT_IF_FALSE(current_scene);
			m_current_scene = current_scene;

			LSPtr<EventListener> eventListener = TryCast<Scene::LevSceneEventListener, EventListener>(current_scene->GetEventListener());
			LEV_ASSERT(eventListener);
			m_event_system->AddEventListener(INPUT_EVENT, eventListener.Get());

			return true;
		}

		bool LevViewer::HasAttachedScene() const
		{
			return m_current_scene.Get();
		}

		void LevViewer::TickFrame()
		{
			m_event_system->DispatchEvent();
			m_window->Update();
			m_current_scene->Update();

			if (m_current_scene->HasModified())
			{
				m_current_scene->SetNodeModified();
				m_current_scene->UpdateWorldTransform();
				m_renderer->SetInputData(m_current_scene->GetSceneData());

				// Scene update must be later than render update, because it will overwrite modified state info.
				m_current_scene->UpdateNodeState();

				m_current_scene->ResetModified();
			}

			if (!m_window->HasStoped())
			{
				m_renderer->Update();
			}
		}

		void LevViewer::SetStop()
		{
			m_window->SetStop();
			TickFrame();
		}

		bool LevViewer::HasStoped()
		{
			return m_window->HasStoped();
		}

		const ILevWindow & LevViewer::GetRenderWindow() const
		{
			return *m_window;
		}

	}
}
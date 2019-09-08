/*
	LevViewer is class which monitor window resource and update data once a frame.
	In common situation, viewer has one window which attach one renderer, but it can do scene update without rendering anything.
*/

#pragma once
#include "LevViewerAPIDefine.h"
#include "LSPtr.h"

namespace Leviathan
{
	class ILevWindow;
	class EventSystem;

	namespace Scene
	{
		class LevScene;
	}

	namespace Renderer
	{
		class IRendererBackend;
	}

	namespace Viewer
	{
		class LEV_VIEWER_API LevViewer
		{
		public:
			LevViewer();
			bool CreateRenderWindow(int width, int height, unsigned handle);
			bool ResizeWindow(int width, int height);

			bool SetCurrentScene(LSPtr<Scene::LevScene> current_scene);
			bool HasAttachedScene() const;

			void TickFrame();
			void SetStop();
			bool HasStoped();

			const ILevWindow& GetRenderWindow() const;

		private:
			LSPtr<EventSystem> m_event_system;
			LSPtr<ILevWindow> m_window;
			LSPtr<Scene::LevScene> m_current_scene;
			LSPtr<Renderer::IRendererBackend> m_renderer;
		};
	}
}
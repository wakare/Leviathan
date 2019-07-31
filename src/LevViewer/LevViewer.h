/*
	LevViewer is class which monitor window resource and update data once a frame.
	In common situation, viewer has one window which attach one renderer, but it can do scene update without rendering anything.
*/

#pragma once
#include "LevViewerAPIDefine.h"
#include "LPtr.h"

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
			
			bool SetCurrentScene(LPtr<Scene::LevScene> current_scene);
			bool HasAttachedScene() const;

			void TickFrame();
			void SetStop();
			bool HasStoped();

			const ILevWindow& GetRenderWindow() const;

		private:
			LPtr<EventSystem> m_event_system;
			LPtr<ILevWindow> m_window;
			LPtr<Scene::LevScene> m_current_scene;
			LPtr<Renderer::IRendererBackend> m_renderer;
		};
	}
}
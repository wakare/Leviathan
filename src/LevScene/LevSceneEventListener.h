#pragma once
#include "EventListener.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevScene;
		class LevCamera;

		class LEV_SCENE_API LevSceneEventListener : public EventListener
		{
		public:
			LevSceneEventListener(LevScene& scene);
			void Accept(Event& event);

		private:
			LevCamera& _camera();

			bool _handleResize(Event& event);
			bool _handleCameraTransform(Event& event);

			LevScene& m_scene;
		};
	}
}
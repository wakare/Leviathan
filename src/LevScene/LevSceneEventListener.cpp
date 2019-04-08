#include "LevSceneEventListener.h"
#include "LevScene.h"
#include "Event.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneEventListener::LevSceneEventListener(LevScene& scene):
			m_scene(scene)
		{

		}

		void LevSceneEventListener::Accept(Event & event)
		{
			switch (event.m_action)
			{
			case Event::RESIZE:
				_handleResize(event);
				break;
			}

		}

		bool LevSceneEventListener::_handleResize(Event & event)
		{
			auto _width = event.m_context.m_windowResizeSize.width;
			auto _height = event.m_context.m_windowResizeSize.height;
			m_scene.SetViewport(_width, _height);

			return true;
		}
	}
}
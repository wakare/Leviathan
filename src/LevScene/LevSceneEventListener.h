#pragma once
#include "EventListener.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevScene;

		class LevSceneEventListener : public EventListener
		{
		public:
			LevSceneEventListener(LevScene& scene);
			void Accept(Event& event);

		private:
			bool _handleResize(Event& event);

			LevScene& m_scene;
		};
	}
}
#pragma once

#include "GlobalDef.h"
#include "LevScene.h"
#include <map>

namespace Leviathan
{
	using namespace Scene;

	namespace UI
	{
		struct UIRect
		{
			unsigned x;
			unsigned y;
			unsigned width;
			unsigned height;
		};

		struct UIElement
		{
			UIRect rect;
			UIElement* parent;


		};

		class LevUISystem
		{
		public:
			LevUISystem();
			UNIQUE_INSTANCE(LevUISystem)

			void AddUIRect(unsigned ui_layer_index, LSPtr<UIRect> ui_rect);

		private:
			void _setupUItoUIScene();

			LSPtr<LevScene> m_ui_scene;
			LSPtr<UIRect> m_root_ui_rect;

			std::map<unsigned, LSPtr<UIRect>> m_ui_rects;
		};
	}
}
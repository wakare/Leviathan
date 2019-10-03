#pragma once
#include "LevSceneRenderAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevRAttrVisible : public LevSceneRenderAttribute
		{
		public: 
			LevRAttrVisible(bool visible);

			ADD_RENDER_ATTRIBUTE_IMPLEMENT(LevRAttrVisible);
			void SetVisible(bool visible);
			bool GetVisible() const;

		private:
			bool m_visible;
		};
	}
}
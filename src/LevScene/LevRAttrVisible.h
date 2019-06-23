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
			void SetVisible(bool visible);
			bool GetVisible() const;

		private:
			bool m_visible;
		};
	}
}
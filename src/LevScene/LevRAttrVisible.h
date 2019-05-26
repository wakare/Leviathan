#pragma once
#include "LevSceneRenderAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevRAttrVisible : public LevSceneRenderAttribute
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
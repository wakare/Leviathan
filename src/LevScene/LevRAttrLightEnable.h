#pragma once
#include "LevSceneRenderAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevRAttrLightEnable : public LevSceneRenderAttribute
		{
		public:
			LevRAttrLightEnable(bool enable);
			void SetLightEnable(bool enable);
			bool GetLightEnable() const;

		private:
			bool m_light_enable;
		};
	}
}
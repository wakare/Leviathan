#pragma once
#include "LevSceneRenderAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevRAttrLightEnable : public LevSceneRenderAttribute
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
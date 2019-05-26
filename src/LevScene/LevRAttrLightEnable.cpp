#include "LevRAttrLightEnable.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrLightEnable::LevRAttrLightEnable(bool enable)
			: LevSceneObjectAttribute(ELSOAT_RENDER)
		{
			SetLightEnable(enable);
		}

		void LevRAttrLightEnable::SetLightEnable(bool enable)
		{
			m_light_enable = enable;
		}

		bool LevRAttrLightEnable::GetLightEnable() const
		{
			return m_light_enable;
		}

	}
}
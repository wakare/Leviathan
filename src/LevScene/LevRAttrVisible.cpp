#include "LevRAttrVisible.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrVisible::LevRAttrVisible(bool visible)
			: LevSceneObjectAttribute(ELSOAT_RENDER)
		{
			SetVisible(visible);
		}

		void LevRAttrVisible::SetVisible(bool visible)
		{
			m_visible = visible;
		}

		bool LevRAttrVisible::GetVisible() const
		{
			return m_visible;
		}
	}
}
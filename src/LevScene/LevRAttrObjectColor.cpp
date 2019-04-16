#include <string.h>
#include "LevRAttrObjectColor.h"
#include "GlobalDef.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrObjectColor::LevRAttrObjectColor(LevObjectColorType type, LPtr<LevObjectColorData> pColorData)
			: m_colorType(type)
			, m_pColorData(pColorData)
		{

		}

		LevRAttrObjectColor::~LevRAttrObjectColor()
		{
		}

		const LevObjectColorType & LevRAttrObjectColor::GetColorType() const
		{
			return m_colorType;
		}

		const LevObjectColorData & LevRAttrObjectColor::GetColorData() const
		{
			return *m_pColorData;
		}

	}
}
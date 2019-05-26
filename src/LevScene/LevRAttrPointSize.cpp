#include "LevRAttrPointSize.h"
#include "GlobalDef.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrPointSize::LevRAttrPointSize(unsigned size)
			: LevSceneObjectAttribute(ELSOAT_RENDER)
		{
			auto seted = SetSize(size);
			LEV_ASSERT(seted);
		}

		bool LevRAttrPointSize::SetSize(unsigned size)
		{
			LEV_ASSERT(size);
			m_size = size;
			return true;
		}

		unsigned LevRAttrPointSize::GetSize() const
		{
			return m_size;
		}

	}
}
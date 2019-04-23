#include "LevSceneObjectAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneObjectAttribute::LevSceneObjectAttribute(int type)
			: m_type(type)
		{

		}
		LevSceneObjectAttribute::~LevSceneObjectAttribute()
		{
		}

		int LevSceneObjectAttribute::GetType() const
		{
			return m_type;
		}
	}
}

#include "LevSceneObjectAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneObjectAttribute::LevSceneObjectAttribute(SceneObjectAttributeType type)
			: m_type(type)
		{

		}
		LevSceneObjectAttribute::~LevSceneObjectAttribute()
		{
		}
		SceneObjectAttributeType LevSceneObjectAttribute::GetType() const
		{
			return m_type;
		}
	}
}

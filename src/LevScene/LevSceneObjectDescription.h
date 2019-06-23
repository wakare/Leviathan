#pragma once

#include "GlobalDef.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevSceneObjectDescription
		{
		public:
			LevSceneObjectDescription(LevSceneObjectDescType descType);
			virtual ~LevSceneObjectDescription();

			LevSceneObjectDescType GetType() const;

		private:
			LevSceneObjectDescType m_type;
		};
	}
}
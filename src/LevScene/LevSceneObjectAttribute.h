#pragma once

#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		enum SceneObjectAttributeType
		{
			ELSOAT_LOGIC,
			ELSOAT_RENDER,
		};

		class LEV_SCENE_API LevSceneObjectAttribute
		{
		public:
			LevSceneObjectAttribute(int type);
			virtual ~LevSceneObjectAttribute();

			int GetType() const;

		private:
			int m_type;
		};
	}
}
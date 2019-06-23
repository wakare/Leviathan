#pragma once
#include "LevSceneRenderAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevRAttrPointSize : public LevSceneRenderAttribute
		{
		public:
			LevRAttrPointSize(unsigned size);
			bool SetSize(unsigned size);
			unsigned GetSize() const;

		private:
			unsigned m_size;
		};
	}
}

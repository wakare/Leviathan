#pragma once

namespace Leviathan
{
	namespace Scene
	{
		enum SceneObjectAttributeType
		{
			ESOLAT_LOGIC,
			ESOLAT_RENDER,
		};

		class LevSceneObjectAttribute
		{
		public:
			LevSceneObjectAttribute(SceneObjectAttributeType type);
			~LevSceneObjectAttribute();

		private:
			SceneObjectAttributeType m_type;
		};
	}
}
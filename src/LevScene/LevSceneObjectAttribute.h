#pragma once

namespace Leviathan
{
	namespace Scene
	{
		enum SceneObjectAttributeType
		{
			ELSOAT_LOGIC,
			ELSOAT_RENDER,
		};

		class LevSceneObjectAttribute
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
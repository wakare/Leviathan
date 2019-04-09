#include "LevSceneData.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneData::LevSceneData()
		{

		}

		LevSceneTree & LevSceneData::GetSceneTree()
		{
			return *m_pSceneTree;
		}

		const Leviathan::Scene::LevSceneTree& LevSceneData::GetSceneTree() const
		{
			return *m_pSceneTree;
		}

	}
}
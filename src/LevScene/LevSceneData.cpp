#include "LevSceneData.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneData::LevSceneData()
		{

		}

		const Leviathan::Scene::LevSceneTree& LevSceneData::GetSceneTree()
		{
			return *m_pSceneTree;
		}

	}
}
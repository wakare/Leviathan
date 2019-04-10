#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevCamera.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneData::LevSceneData()
			:m_pSceneTree(new LevSceneTree)
		{
			// FOR DEBUG
			LPtr<LevCamera> pCamera = new LevCamera;
			float eye[3] = { 0.0f, 0.0f, 0.0f };
			float up[3] = { 0.0f, 1.0f, 0.0f };
			float look[3] = { 0.0f, 0.0f, -1.0f };
			LEV_ASSERT(pCamera->Set(eye, look, up, 90.0f, 1.0f, 0.01f, 1000.0f));
			LPtr<LevSceneNode> pNode = new LevSceneNode(TryCast<LevCamera, LevSceneObject>(pCamera));
			m_pSceneTree->AddNode(pNode);
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
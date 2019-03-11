#include <filesystem>
#include "TriDScene.h"
#include "SceneNode.h"
#include "DrawableNode.h"
#include "SceneGraph.h"
#include "GlobalDef.h"
#include "SceneHelper.h"
#include "SceneLogicDataSet.h"
#include "TriDObjectGLPass.h"

namespace Leviathan
{
	TriDScene::TriDScene(GLFWwindow* pRenderWindow, int width, int height):
		CommonScene(pRenderWindow, width, height)
	{

	}

	bool TriDScene::AddNode(LPtr<Node<SceneNode>> pNode)
	{
		EXIT_IF_FALSE(m_pSceneLogicData->AddNode(pNode));
		return true;
	}

	bool TriDScene::AddMesh(const char* filePath, bool resetCameraToMeshCenter /*= false*/)
	{
		LPtr<Node<SceneNode>> pModelNode;
		std::string path = std::experimental::filesystem::current_path().string() + std::string(filePath);
		EXIT_IF_FALSE(SceneHelper::LoadModel(path.c_str(), pModelNode));
		m_pSceneLogicData->AddNode(pModelNode);
		pModelNode->GetNodeData()->SetWorldCoord({ 0.0f, 0.0f, 0.0f });

		if (resetCameraToMeshCenter)
		{
			AABB nodeAABB; EXIT_IF_FALSE(pModelNode->GetNodeData()->GetModelAABB(nodeAABB));
			_resetCamera(nodeAABB.center);
		}

		return true;
	}

	bool TriDScene::_firstUpdate()
	{
		// Init light
		EXIT_IF_FALSE(_initLight());
		if (!_initSceneObject()) LogLine("[ERROR] Init scene object failed."); 
		return true;
	}

	bool TriDScene::_initSceneObject()
	{
		//EXIT_IF_FALSE(AddMesh("\\2b\\lufeng.FBX", true));
		EXIT_IF_FALSE(AddMesh("\\Black_Dragon\\Dragon_2.5_fbx.FBX", true));
		return true;
	}

}
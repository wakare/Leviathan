#include <filesystem>
#include "TriDScene.h"
#include "SceneNode.h"
#include "DrawableNode.h"
#include "SceneGraph.h"
#include "GlobalDef.h"
#include "SceneHelper.h"
#include "SceneLogicDataSet.h"

namespace Leviathan
{
	TriDScene::TriDScene(GLFWwindow* pRenderWindow, int width, int height):
		CommonScene(pRenderWindow, width, height)
	{

	}

	bool TriDScene::_firstUpdate()
	{
		// Init light
		EXIT_GET_FALSE(_initLight());
		if (!_initSceneObject()) LogLine("[ERROR] Init scene object failed."); 
		return true;
	}

	bool TriDScene::_initSceneObject()
	{
		LPtr<Node<SceneNode>> pModelNode;
		std::string path = std::experimental::filesystem::current_path().string() + "\\Models\\SoccerBall.STL";
		EXIT_GET_FALSE(SceneHelper::LoadModel(path.c_str(), pModelNode));
		m_pSceneLogicData->AddNode(pModelNode);
		AABB nodeAABB; EXIT_GET_FALSE(pModelNode->GetNodeData()->GetAABB(nodeAABB));
		_resetCamera(nodeAABB.center);
		return true;
	}

}
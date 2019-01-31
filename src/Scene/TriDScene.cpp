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
		if (!_initSceneObject())  LeviathanOutStream << "[ERROR] Init scene object failed." << std::endl; 
		_resetCamera();
		return true;
	}

	bool TriDScene::_initSceneObject()
	{
		LPtr<Node<SceneNode>> pModelNode;
		std::string path = std::experimental::filesystem::current_path().string() + "\\Black_Dragon\\Dragon_2.5_fbx.fbx";
		EXIT_GET_FALSE(SceneHelper::LoadModel(path.c_str(), pModelNode));
		m_pSceneLogicData->AddNode(pModelNode);
		_resetCamera();
		return true;
	}

}
#include "TriDScene.h"
#include "SceneNode.h"
#include "DrawableNode.h"
#include "SceneGraph.h"
#include "GlobalDef.h"
#include "SceneHelper.h"

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

		if (!_initSceneObject())
		{
			LeviathanOutStream << "[ERROR] Init scene object failed." << std::endl;
		}

		_resetCamera();

		return true;
	}

	bool TriDScene::_initSceneObject()
	{
		LPtr<Node<SceneNode>> pModelNode;
		EXIT_GET_FALSE(SceneHelper::LoadModel("C:/Users/msi-cn/Documents/Visual Studio 2017/Projects/Leviathan/src/Leviathan/2b/lufeng.FBX", pModelNode));
		m_pSceneGraph->AddNode(pModelNode);

		_resetCamera();
		return true;
	}

}
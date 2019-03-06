#pragma once

#include "CommonScene.h"

namespace Leviathan
{ 
	class TriDScene : public CommonScene
	{
	public:
		TriDScene(GLFWwindow* pRenderWindow, int width, int height);
		bool AddNode(LPtr<Node<SceneNode>> pNode);
		bool AddMesh(const char* filePath);

	private:
		bool _firstUpdate();
		bool _initSceneObject();
	};
}
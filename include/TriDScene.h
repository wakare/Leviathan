#pragma once
#include "CommonScene.h"

namespace Leviathan
{ 
	class TriDScene : public CommonScene
	{
	public:
		TriDScene(GLFWwindow* pRenderWindow, int width, int height);

		bool _firstUpdate();
		bool _initSceneObject();
	};
}
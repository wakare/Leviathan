#pragma once
#include "CommonScene.h"
#include "PointCloud.h"

namespace Leviathan
{
	class PointCloudScene : public CommonScene
	{
	public:
		PointCloudScene(GLFWwindow* pRenderWindow, int width, int height);
		void UpdatePointCloud(PointCloudf& pPoints);

	private:
		bool _firstUpdate();
		bool _initSceneObject();
	};
}

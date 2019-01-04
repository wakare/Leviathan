#pragma once
#include "CommonScene.h"

namespace Leviathan
{
	class PointCloudScene : public CommonScene
	{
	public:
		PointCloudScene(GLFWwindow* pRenderWindow, int width, int height);

		void UpdatePointCloud(PointCloudf& pPoints);
		bool _firstUpdate();
		virtual bool _initSceneObject();

	private:

	};
}

#pragma once

#include "Singleton.h"
#include "LPtr.h"

namespace Leviathan
{
	class ViewScheduler;

	namespace Scene
	{
		class LevSceneNode;
	}

	class UserInterface
	{
	public:
		struct BaseData
		{
			int windowHandle;
		};

		static void Init(int width, int height, int parentHandle);
		static void UpdatePresenter();
		static void Stop();
		
		static const BaseData& GetData();
		static bool LoadMeshFile(const char * file);
		static bool LoadPointCloudFile(const char * file, LPtr<Scene::LevSceneNode>& out);
		static bool AddNodeToScene(LPtr<Scene::LevSceneNode> pNode);

		static ViewScheduler& GetViewScheduler();

	private:
		static BaseData m_data;
	};
}
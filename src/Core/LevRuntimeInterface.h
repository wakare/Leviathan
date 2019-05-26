#pragma once

#include "Singleton.h"
#include "PointCloud.h"
#include "LPtr.h"
#include "LevCoroutine.h"

namespace Leviathan
{
	class ViewScheduler;

	namespace Scene
	{
		class LevSceneNode;
	}

	class LevRuntimeInterface
	{
	public:
		struct LevRuntimeData
		{
			int windowHandle;
		};
		 
		static void Init(int width, int height, int parentHandle);
		static void Update();
		static void Stop();
		
		static const LevRuntimeData& GetRuntimeData();
		static bool LoadMesh(const char * file);
		static bool LoadPointCloud(const char * file, LPtr<Scene::LevSceneNode>& out);
		static bool LoadPointCloud(const PointCloudf& point_cloud, LPtr<Scene::LevSceneNode>& out);
		static bool AddNodeToScene(LPtr<Scene::LevSceneNode> pNode);

		static void AddAsyncTaskToView(std::function<void(CoPullType<int>&)> task);
		static void AddSyncTaskToView(std::function<void(CoPullType<int>&)> task);

		static ViewScheduler& GetViewScheduler();

	private:
		static LevRuntimeData m_data;
	};
}
#pragma once

#include "LevScheduler.h"
#include "TriDScene.h"
#include "PointCloud.h"
#include "ThreadRecorder.h"
#include "View.h"

namespace Leviathan 
{
	class IMesh;

	class ViewScheduler : public LevScheduler<int>, public ThreadRecorder
	{
	public:
		UNIQUE_INSTANCE(ViewScheduler)

		ViewScheduler();
		void Update();
		void SetDone();

		bool Sync_Init(int width, int height, int parentHandle);

		int Sync_GetWindowHandle();

		bool Async_LoadMeshFile(const char* file);
		bool Sync_LoadPointCloudFile(const char* file, LPtr<Scene::LevSceneNode>& out);
		bool Sync_LoadPointCloud(const PointCloudf& point_cloud, LPtr<Scene::LevSceneNode>& out);
		bool Async_AddNode(LPtr<Scene::LevSceneNode> pNode);
		bool Async_LoadCustomMesh(LPtr<IMesh> pMesh);

	private:
		bool m_done;
		std::unique_ptr<View> m_pView;
	};
}
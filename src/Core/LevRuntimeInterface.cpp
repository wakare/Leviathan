#include "LevRuntimeInterface.h"
#include "PresenterScheduler.h"
#include "ViewScheduler.h"
#include "LevSceneNode.h"

namespace Leviathan
{
	LevRuntimeInterface::LevRuntimeData LevRuntimeInterface::m_data;

	inline PresenterScheduler& _scheduler()
	{
		return PresenterScheduler::Instance();
	}

	void LevRuntimeInterface::Init(int width, int height, int parentHandle)
	{	
		LEV_ASSERT(_scheduler().GetAppState() == EAS_UNINITED);
		_scheduler().SetState(EAS_INITING);
		auto inited = _scheduler().GetViewScheduler().Sync_Init(width, height, parentHandle);
		LEV_ASSERT(inited);
		_scheduler().SetState(EAS_INITED);
	}

	void LevRuntimeInterface::Update()
	{
		if (_scheduler().GetAppState() > EAS_INITING)
		{
			_scheduler().Update();
		}
	}

	void LevRuntimeInterface::Stop()
	{
		_scheduler().SetDone();
	}

	const LevRuntimeInterface::LevRuntimeData& LevRuntimeInterface::GetRuntimeData()
	{
		m_data.windowHandle = PresenterScheduler::Instance().GetViewScheduler().Sync_GetWindowHandle();
		return m_data;
	}

	Leviathan::ViewScheduler& LevRuntimeInterface::GetViewScheduler()
	{
		return _scheduler().GetViewScheduler();
	}

	bool LevRuntimeInterface::LoadMesh(const char * file)
	{
		return _scheduler().GetViewScheduler().Async_LoadMeshFile(file);
	}

	bool LevRuntimeInterface::LoadPointCloud(const char * file, LPtr<Scene::LevSceneNode>& out)
	{
		return _scheduler().GetViewScheduler().Sync_LoadPointCloudFile(file, out);
	}

	bool LevRuntimeInterface::LoadPointCloud(const PointCloudf& point_cloud, LPtr<Scene::LevSceneNode>& out)
	{
		return _scheduler().GetViewScheduler().Sync_LoadPointCloud(point_cloud, out);
	}

	bool LevRuntimeInterface::AddNodeToScene(LPtr<Scene::LevSceneNode> pNode)
	{
		return _scheduler().GetViewScheduler().Async_AddNode(pNode);
	}

	void LevRuntimeInterface::AddAsyncTaskToView(std::function<void(CoPullType<int>&)> task)
	{
		_scheduler().GetViewScheduler().DoAsyncTask(task);
	}

	void LevRuntimeInterface::AddSyncTaskToView(std::function<void(CoPullType<int>&)> task)
	{
		_scheduler().GetViewScheduler().DoSyncTask(task);
	}

}
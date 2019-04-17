#include "UserInterface.h"
#include "PresenterScheduler.h"
#include "ViewScheduler.h"
#include "LevSceneNode.h"

namespace Leviathan
{
	UserInterface::BaseData UserInterface::m_data;

	PresenterScheduler& _scheduler()
	{
		return PresenterScheduler::Instance();
	}

	void UserInterface::Init(int width, int height, int parentHandle)
	{	
		LEV_ASSERT(_scheduler().GetAppState() == EAS_UNINITED);
		_scheduler().SetState(EAS_INITING);
		auto inited = _scheduler().GetViewScheduler().Init(width, height, parentHandle);
		LEV_ASSERT(inited);
		_scheduler().SetState(EAS_INITED);
	}

	void UserInterface::UpdatePresenter()
	{
		if (_scheduler().GetAppState() > EAS_INITING)
		{
			_scheduler().Update();
		}
	}

	void UserInterface::Stop()
	{
		_scheduler().SetDone();
	}

	const UserInterface::BaseData& UserInterface::GetData()
	{
		m_data.windowHandle = PresenterScheduler::Instance().GetViewScheduler().GetWindowHandle();
		return m_data;
	}

	Leviathan::ViewScheduler& UserInterface::GetViewScheduler()
	{
		return _scheduler().GetViewScheduler();
	}

	bool UserInterface::LoadMeshFile(const char * file)
	{
		return _scheduler().GetViewScheduler().LoadMeshFile(file);
	}

	bool UserInterface::LoadPointCloudFile(const char * file, LPtr<Scene::LevSceneNode>& out)
	{
		return _scheduler().GetViewScheduler().LoadPointCloudFile(file, out);
	}

}
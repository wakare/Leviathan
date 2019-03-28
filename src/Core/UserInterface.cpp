#include "UserInterface.h"
#include "PresenterScheduler.h"
#include "ViewScheduler.h"

namespace Leviathan
{
	PresenterScheduler& _scheduler()
	{
		return PresenterScheduler::Instance();
	}

	void UserInterface::Init(int width, int height, int parentHandle)
	{		
		auto& scheduler = _scheduler();
		_scheduler().GetViewScheduler().AddTask([=](CoPullType<int>& sink)
		{
			PresenterScheduler::Instance().GetViewScheduler().Init(width, height, parentHandle);
		});
	}

	void UserInterface::Update()
	{
		_scheduler().Update();
	}

	void UserInterface::Stop()
	{
		_scheduler().SetDone();
	}

	BaseData UserInterface::GetData()
	{
		return m_data;
	}
}
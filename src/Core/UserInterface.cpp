#include "UserInterface.h"
#include "PresenterScheduler.h"
#include "ViewScheduler.h"

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
		LEV_ASSERT(_scheduler().GetViewScheduler().Init(width, height, parentHandle));
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
}
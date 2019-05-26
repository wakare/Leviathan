#include "DebugModule.h"

namespace SOFilter
{
	DebugModule::DebugModule()
		: m_debug_state(EDS_UNKNOWN)
	{
		auto _debug_task = [this](CoPullType<int>& sink)
		{


		};

		DoAsyncTask(_debug_task);
	}

	void DebugModule::DebugStart()
	{
		_debugStateChange(EDS_START);
	}

	void DebugModule::DebugStop()
	{
		_debugStateChange(EDS_STOP);
	}

	void DebugModule::DebugTick()
	{
		_debugStateChange(EDS_TICK);
	}

	void DebugModule::DebugRollback()
	{
		_debugStateChange(EDS_ROLLBACK);
	}

	void DebugModule::Update()
	{
		_tick();
	}

	void DebugModule::_debugStateChange(DebugState state)
	{
		auto _state_change = [this, state](CoPullType<int>& sink)
		{
			
		};

		DoAsyncTask(_state_change);
	}
}

#pragma once

#include "LevScheduler.h"

using namespace Leviathan;

namespace SOFilter
{
	enum DebugState
	{
		EDS_UNKNOWN,
		EDS_START,
		EDS_STOP,
		EDS_TICK,
		EDS_ROLLBACK
	};

	class DebugModule : public LevScheduler<int>
	{
	public:
		DebugModule();

		void DebugStart();
		void DebugStop();
		void DebugTick(); 
		void DebugRollback();

		void Update();

	private:
		void _debugStateChange(DebugState state);

		DebugState m_debug_state;
	};
}
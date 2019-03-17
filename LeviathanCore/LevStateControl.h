#pragma once

namespace Leviathan
{
	enum ELevState
	{
		ELS_UNINITED	= 0,
		ELS_INITING		= 1,
		ELS_INITED		= 2,
		ELS_RUNNING		= 3,
		ELS_STOPPING	= 4,
		ELS_STOPED		= 5,

		ELS_UNKNOWN		= 1000,
	};

	class LevStateControl
	{
	public:
		LevStateControl();
		bool StateChange(ELevState state);

	private:
		bool _enterState(ELevState state);
		bool _state_enter_UnInited();
		bool _state_enter_Initing();
		bool _state_enter_Inited();
		bool _state_enter_Running();
		bool _state_enter_Stopping();
		bool _state_enter_Stopped();

		ELevState m_state;
	};
}
#pragma once

namespace Leviathan
{
	enum ELevState
	{
		ELS_UNINITED,
		ELS_INITING,
		ELS_INITED,
		ELS_RUNNING,
		ELS_STOPPING,
		ELS_STOPED
	};

	class LevStateControl
	{
	public:
		LevStateControl();
		bool StateChange(ELevState state);

	private:
		void _enterState(ELevState state);
		ELevState m_state;
	};
}
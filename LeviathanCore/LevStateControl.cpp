#include "LevStateControl.h"
#include "KLog.h"

namespace Leviathan
{
	LevStateControl::LevStateControl():
		m_state(ELS_UNKNOWN)
	{

	}

	bool LevStateControl::StateChange(ELevState state)
	{
		if (state <= m_state) { 
			return false; 
		}

		return _enterState(state);
	}

	bool LevStateControl::_enterState(ELevState state)
	{
		while (m_state <= state) {
			m_state = static_cast<ELevState>(static_cast<unsigned>(m_state) + 1);
			bool bSucceed = false;

			switch (m_state)
			{
			case ELS_UNINITED:
				bSucceed = _state_enter_UnInited();
				break;

			case ELS_INITING:
				bSucceed = _state_enter_Initing();
				break;

			case ELS_INITED:
				bSucceed = _state_enter_Inited();
				break;

			case ELS_RUNNING:
				bSucceed = _state_enter_Running();
				break;

			case ELS_STOPPING:
				bSucceed = _state_enter_Stopping();
				break;

			case ELS_STOPED:
				bSucceed = _state_enter_Stopped();
				break;

			case ELS_UNKNOWN:
				KLog::Log("[ERROR] Can not enter state unknown.");
				break;
			}

			if (!bSucceed) {
				return false;
			}
		}

		return true;
	}

	bool LevStateControl::_state_enter_UnInited()
	{
		return true;
	}

	bool LevStateControl::_state_enter_Initing()
	{
		return true;
	}

	bool LevStateControl::_state_enter_Inited()
	{
		return true;
	}

	bool LevStateControl::_state_enter_Running()
	{
		return true;
	}

	bool LevStateControl::_state_enter_Stopping()
	{
		return true;
	}

	bool LevStateControl::_state_enter_Stopped()
	{
		return true;
	}
}
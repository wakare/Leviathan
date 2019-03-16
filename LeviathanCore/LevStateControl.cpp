#include "LevStateControl.h"

namespace Leviathan
{
	LevStateControl::LevStateControl():
		m_state(ELS_UNINITED)
	{

	}
	bool LevStateControl::StateChange(ELevState state)
	{
		if (state <= m_state) { 
			return false; 
		}



		return true;
	}

	void LevStateControl::_enterState(ELevState state)
	{
		while (m_state <= state)
		{
			m_state = static_cast<ELevState>(static_cast<unsigned>(m_state) + 1);

			// Do something

		}
	}
}
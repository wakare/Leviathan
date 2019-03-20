#include "ViewStateMgr.h"

namespace Leviathan
{
	ViewStateMgr::ViewStateMgr():
		m_type(EVS_UNINITED)
	{
	}

	ViewStateType ViewStateMgr::getViewStateType()
	{
		return m_type;
	}
}
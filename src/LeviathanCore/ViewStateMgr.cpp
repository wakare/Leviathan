#include "ViewStateMgr.h"

namespace Leviathan
{
	ViewStateMgr::ViewStateMgr(ViewData& viewData):
		m_type(EVS_UNINITED),
		m_viewData(viewData)
	{
	}

	ViewStateType ViewStateMgr::getViewStateType()
	{
		return m_type;
	}

	void ViewStateMgr::SetViewStateType(ViewStateType type)
	{
		m_type = type;
	}
}
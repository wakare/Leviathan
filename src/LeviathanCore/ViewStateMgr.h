#pragma once

namespace Leviathan
{
	enum ViewStateType
	{
		EVS_UNINITED,
		EVS_INITING,
		EVS_INITED,
		EVS_RUNNING,
		EVS_STOPPING,
		EVS_STOPPED,
	};

	class ViewStateMgr
	{
	public:
		ViewStateMgr();
		ViewStateType getViewStateType();

	private:
		ViewStateType m_type;
	};
}
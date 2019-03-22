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

	class ViewData;

	class ViewStateMgr
	{
	public:
		ViewStateMgr(ViewData& viewData);
		ViewStateType getViewStateType();
		void SetViewStateType(ViewStateType type);

	private:
		ViewStateType m_type;
		ViewData& m_viewData;
	};
}
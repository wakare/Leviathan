#include "RenderCommand.h"
#include "GlobalDef.h"
#include "ViewScheduler.h"
#include "PresenterScheduler.h"

using namespace Leviathan;

namespace SOFilter
{
	inline ViewScheduler& _viewScheduler()
	{
		return PresenterScheduler::Instance().GetViewScheduler();
	}

	RenderCommand::RenderCommand(RenderCommandFunc do_func, RenderCommandFunc undo_func)
		: m_do_func(do_func)
		, m_undo_func(undo_func)
	{

	}

	bool RenderCommand::Do()
	{
		EXIT_IF_FALSE(m_do_func);
		m_do_func();
		// TODO : Render command return value defination 
		return true;
	}

	bool RenderCommand::Undo()
	{
		EXIT_IF_FALSE(m_undo_func);
		m_undo_func();
		// TODO : Render command return value defination 
		return true;
	}
}

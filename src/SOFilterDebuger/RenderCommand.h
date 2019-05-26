#pragma once

#include <functional>
#include "Command.h"
#include "LevCoroutine.h"

using namespace Leviathan;

namespace SOFilter 
{
	typedef std::function<void()> RenderCommandFunc;

	class RenderCommand : public Command
	{
	public:
		RenderCommand(RenderCommandFunc do_func, RenderCommandFunc undo_func);

		bool Do();
		bool Undo();

	private:
		RenderCommandFunc m_do_func;
		RenderCommandFunc m_undo_func;
	};
}
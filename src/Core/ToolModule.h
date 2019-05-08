#pragma once

#include <thread>

namespace Leviathan
{
	class ToolModule
	{
	public:
		ToolModule();

		std::thread::id GetMainModuleThreadID() const;
		bool IsSameThreadOfMainModule() const;

	private:
		std::thread::id m_main_module_thread_id;
	};
}
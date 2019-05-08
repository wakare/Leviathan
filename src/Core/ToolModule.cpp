#include "ToolModule.h"

namespace Leviathan
{
	ToolModule::ToolModule()
		: m_main_module_thread_id(std::this_thread::get_id())
	{

	}

	std::thread::id ToolModule::GetMainModuleThreadID() const
	{
		return m_main_module_thread_id;
	}

	bool ToolModule::IsSameThreadOfMainModule() const
	{
		return std::this_thread::get_id() == m_main_module_thread_id;
	}
}
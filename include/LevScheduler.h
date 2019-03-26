#pragma once

#include <vector>
#include <mutex>

#include "LevTask.h"
#include "LPtr.h"

namespace Leviathan
{
	class LevScheduler
	{
	public:
		void AddTask(LPtr<LevTask> task);
		void AddTask(const std::vector<LPtr<LevTask>>& task);
		void Tick();

	protected:
		LevScheduler();

		std::mutex m_tasks_lock;
		std::vector<LPtr<LevTask>> m_tasks;
	};
}
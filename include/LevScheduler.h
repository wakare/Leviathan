#pragma once

#include <vector>
#include <mutex>

#include "LevTask.h"
#include "LPtr.h"

namespace Leviathan
{
	template <class T>
	class LevScheduler
	{
	public:
		void AddTask(LPtr<LevTaskTemplate<T>> task);
		void AddTask(const std::vector<LPtr<LevTaskTemplate<T>>>& task);
		
	protected:
		void Tick();
		LevScheduler();

		std::mutex m_tasks_lock;
		std::vector<LPtr<LevTaskTemplate<T>>> m_tasks;
	};
}

#include "LevScheduler.hpp"
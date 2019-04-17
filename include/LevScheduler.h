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
		void DoTask(LPtr<LevTaskTemplate<T>> task);
		void DoTask(const std::vector<LPtr<LevTaskTemplate<T>>>& task);
		void DoTask(std::function<void(CoPullType<T>&)> func);

	protected:
		void _tick();

		LevScheduler();

		bool m_executeTaskFlag;
		std::mutex m_tasks_lock;
		std::vector<LPtr<LevTaskTemplate<T>>> m_tasks;
	};
}

#include "LevScheduler.hpp"
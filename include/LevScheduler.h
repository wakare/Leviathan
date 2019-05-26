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
		void DoAsyncTask(LPtr<LevTaskTemplate<T>> task);
		void DoAsyncTask(const std::vector<LPtr<LevTaskTemplate<T>>>& task);
		void DoAsyncTask(std::function<void(CoPullType<T>&)> func);

		bool DoSyncTask(LPtr<LevTaskTemplate<T>> task);
		bool DoSyncTask(std::function<void(CoPullType<T>&)> func);

	protected:
		void _tick();

		LevScheduler();

		bool m_executeTaskFlag;
		std::mutex m_tasks_lock;
		std::vector<LPtr<LevTaskTemplate<T>>> m_tasks;
	};
}

#include "LevScheduler.hpp"
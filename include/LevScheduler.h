#pragma once

#include <vector>
#include <mutex>

#include "LevTask.h"
#include "LSPtr.h"

namespace Leviathan
{
	template <class T>
	class LevScheduler
	{
	public:
		void DoAsyncTask(LSPtr<LevTaskTemplate<T>> task);
		void DoAsyncTask(const std::vector<LSPtr<LevTaskTemplate<T>>>& task);
		void DoAsyncTask(std::function<void(CoPullType<T>&)> func);

		bool DoSyncTask(LSPtr<LevTaskTemplate<T>> task);
		bool DoSyncTask(std::function<void(CoPullType<T>&)> func);

	protected:
		void _tick();

		LevScheduler();

		bool m_executeTaskFlag;
		std::mutex m_tasks_lock;
		std::vector<LSPtr<LevTaskTemplate<T>>> m_tasks;
	};
}

#include "LevScheduler.hpp"
#include "LevScheduler.h"

namespace Leviathan
{
	template <class T>
	void LevScheduler<T>::DoTask(LPtr<LevTaskTemplate<T>> task)
	{
		std::lock_guard<std::mutex> guard(m_tasks_lock);
		m_tasks.push_back(task);
	}

	template <class T>
	void LevScheduler<T>::DoTask(const std::vector<LPtr<LevTaskTemplate<T>>>& task)
	{
		std::lock_guard<std::mutex> guard(m_tasks_lock);
		m_tasks.insert(m_tasks.end(), task.begin(), task.end());
	}

	template <class T>
	void Leviathan::LevScheduler<T>::DoTask(std::function<void(CoPullType<T>&)> func)
	{
		LPtr<LevTaskTemplate<T>> pTask = new LevTaskTemplate<T>(func);
		DoTask(pTask);
	}

	// Warning: DoSyncTask must bu called form non-render thread
	template <class T>
	void LevScheduler<T>::DoSyncTask(LPtr<LevTaskTemplate<T>> task)
	{
		{
			std::lock_guard<std::mutex> guard(m_tasks_lock);
			m_tasks.push_back(task);
		}
		
		// Sync wait
		while (task->Valid())
		{
			Sleep(10);
		}
	}

	// Warning: DoSyncTask must bu called form non-render thread
	template <class T>
	void Leviathan::LevScheduler<T>::DoSyncTask(std::function<void(CoPullType<T>&)> func)
	{
		LPtr<LevTaskTemplate<T>> pTask = new LevTaskTemplate<T>(func);
		DoSyncTask(pTask);
	}

	template <class T>
	void LevScheduler<T>::_tick()
	{
		std::vector<LPtr<LevTaskTemplate<T>>> _tasks;
		{
			std::lock_guard<std::mutex> guard(m_tasks_lock);
			_tasks = m_tasks;
			m_tasks.clear();
		}
		
		std::vector<LPtr<LevTaskTemplate<T>>> remainTasks;
		for (auto& task : _tasks)
		{
			task->Do();

			if (task->Valid()) 
			{
				remainTasks.push_back(task);
			}
		}

		{
			std::lock_guard<std::mutex> guard(m_tasks_lock);
			m_tasks.insert(m_tasks.end(), remainTasks.begin(), remainTasks.end());
			m_executeTaskFlag = true;
		}
	}

	template <class T>
	LevScheduler<T>::LevScheduler()
	{
	}
}
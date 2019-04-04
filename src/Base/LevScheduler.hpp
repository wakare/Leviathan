#include "LevScheduler.h"

namespace Leviathan
{
	template <class T>
	void LevScheduler<T>::AddTask(LPtr<LevTaskTemplate<T>> task)
	{
		m_tasks_lock.lock();
		m_tasks.push_back(task);
		m_tasks_lock.unlock();
	}

	template <class T>
	void LevScheduler<T>::AddTask(const std::vector<LPtr<LevTaskTemplate<T>>>& task)
	{
		m_tasks_lock.lock();
		m_tasks.insert(m_tasks.end(), task.begin(), task.end());
		m_tasks_lock.unlock();
	}

	template <class T>
	void LevScheduler<T>::Tick()
	{
		m_tasks_lock.lock();
		std::vector<LPtr<LevTaskTemplate>> remainTasks;

		for (auto& task : m_tasks)
		{
			task->Do();

			if (task->Valid()) 
			{
				remainTasks.push_back(task);
			}
		}

		m_tasks = remainTasks;
		m_tasks_lock.unlock();
	}

	template <class T>
	LevScheduler<T>::LevScheduler()
	{
	}
}
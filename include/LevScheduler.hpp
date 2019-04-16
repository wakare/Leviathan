#include "LevScheduler.h"

namespace Leviathan
{
	template <class T>
	void LevScheduler<T>::AddTask(LPtr<LevTaskTemplate<T>> task)
	{
		std::lock_guard<std::mutex> guard(m_tasks_lock);
		m_tasks.push_back(task);
	}

	template <class T>
	void LevScheduler<T>::AddTask(const std::vector<LPtr<LevTaskTemplate<T>>>& task)
	{
		std::lock_guard<std::mutex> guard(m_tasks_lock);
		m_tasks.insert(m_tasks.end(), task.begin(), task.end());
	}

	template <class T>
	void Leviathan::LevScheduler<T>::AddTask(std::function<void(CoPullType<T>&)> func)
	{
		LPtr<LevTaskTemplate<T>> pTask = new LevTaskTemplate<T>(func);
		AddTask(pTask);
	}

	template <class T>
	void LevScheduler<T>::Tick()
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
		}
	}

	template <class T>
	LevScheduler<T>::LevScheduler()
	{
	}
}
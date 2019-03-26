#include "LevScheduler.h"

namespace Leviathan
{
	void LevScheduler::AddTask(LPtr<LevTask> task)
	{
		m_tasks_lock.lock();
		m_tasks.push_back(task);
		m_tasks_lock.unlock();
	}

	void LevScheduler::AddTask(const std::vector<LPtr<LevTask>>& task)
	{
		m_tasks_lock.lock();
		m_tasks.insert(m_tasks.end(), task.begin(), task.end());
		m_tasks_lock.unlock();
	}

	void LevScheduler::Tick()
	{
		m_tasks_lock.lock();
		std::vector<LPtr<LevTask>> remainTasks;

		for (auto& task : m_tasks)
		{
			task->Do();
			if (task->Type() == ET_ALWARYS) 
			{
				remainTasks.push_back(task);
			}
		}

		m_tasks = remainTasks;
		m_tasks_lock.unlock();
	}

	LevScheduler::LevScheduler()
	{
	}
}
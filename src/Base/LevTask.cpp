#include "LevTask.h"

namespace Leviathan
{
	LevTask::LevTask(LevTaskType type, TaskFunc func):
		m_type(type),
		m_func(func)
	{

	}

	LevTask::~LevTask()
	{
	}

	void LevTask::Do()
	{
		m_func();
	}

	LevTaskType LevTask::Type() const
	{
		return m_type;
	}
}
#pragma once

#include <functional>

namespace Leviathan
{
	enum LevTaskType
	{
		ET_ONCE,
		ET_ALWARYS
	};

	class LevTask
	{
	public:
		typedef std::function<void()> TaskFunc;
		LevTask(LevTaskType type, TaskFunc func);
		~LevTask();

		virtual void Do();
		LevTaskType Type() const;

	protected:
		LevTask(const LevTask& task) = delete;
		LevTask& operator=(const LevTask& task) = delete;
		LevTask(const LevTask&& task) = delete;
		LevTask& operator=(const LevTask&& task) = delete;

		TaskFunc m_func;
		LevTaskType m_type;
	};
}
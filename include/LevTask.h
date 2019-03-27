#pragma once

#include "LevCoroutine.h"

namespace Leviathan
{
	template <class T>
	class LevTaskTemplate
	{
	public:
		LevTaskTemplate(LevCoroutine<T> func);
		~LevTaskTemplate();

		virtual void Do(T input = T());
		
		bool Valid() const;

	protected:
		LevTaskTemplate(const LevTaskTemplate& task) = delete;
		LevTaskTemplate& operator=(const LevTaskTemplate& task) = delete;
		LevTaskTemplate(const LevTaskTemplate&& task) = delete;
		LevTaskTemplate& operator=(const LevTaskTemplate&& task) = delete;

		LevCoroutine<T> m_func;
	};
}

#include "LevTask.hpp"

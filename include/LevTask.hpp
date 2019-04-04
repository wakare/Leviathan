#include "LevTask.h"

namespace Leviathan
{
	template<class T>
	LevTaskTemplate<T>::LevTaskTemplate(LevCoroutine<T> func):
		m_func(std::move(func))
	{

	}

	template<class T>
	LevTaskTemplate<T>::~LevTaskTemplate()
	{
	}

	template<class T>
	void LevTaskTemplate<T>::Do(T input)
	{
		m_func.Tick(input);
	}

	template<class T>
	bool LevTaskTemplate<T>::Valid() const
	{
		return m_func.Valid();
	}
}
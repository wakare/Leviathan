#pragma once
#include "LevCoroutine.h"

namespace Leviathan
{
	template<class T>
	inline LevCoroutine<T>::LevCoroutine(std::function<void(CoPullType<typename T>&)> func):
		m_caller(func)
	{
		
	}

	template<class T>
	inline void LevCoroutine<T>::Tick(T t)
	{
		m_caller(t);
	}

	template<class T>
	inline bool LevCoroutine<T>::Valid() const
	{
		return static_cast<bool>(m_caller);
	}
}
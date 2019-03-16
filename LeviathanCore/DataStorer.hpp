#pragma once

#include "DataStorer.h"

namespace Leviathan
{
	template<typename T>
	inline DataStorer<T>::DataStorer()
	{
	}

	template <typename T>
	bool DataStorer<T>::Store(std::unique_ptr<T> obj)
	{
		m_data[handle] = std::move(obj);
	}

	template <typename T>
	const T& DataStorer<T>::Get(DataHandle handle) const
	{
		return *m_data[handle];
	}

	template <typename T>
	T& DataStorer<T>::Get(DataHandle handle)
	{
		return *m_data[handle];
	}
}
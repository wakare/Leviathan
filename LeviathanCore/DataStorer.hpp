#pragma once

#include "DataStorer.h"

	template<typename T>
	inline Leviathan::DataStorer<T>::DataStorer()
	{
	}

	template <typename T>
	Leviathan::DataHandle Leviathan::DataStorer<T>::Store(std::unique_ptr<T> obj)
	{
		DataHandle handle = m_data.size();
		m_data[handle] = std::move(obj);
		return handle;
	}

	template <typename T>
	const T& Leviathan::DataStorer<T>::Get(Leviathan::DataHandle handle) const
	{
		return *m_data[handle];
	}

	template <typename T>
	T& Leviathan::DataStorer<T>::Get(DataHandle handle)
	{
		return *m_data[handle];
	}
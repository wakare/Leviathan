#pragma once

namespace Leviathan
{
	/*
	 * TODO: Replace DynamicArray with RAIIBufferData
	 */
	template<class T>
	class DynamicArray
	{
	public:
		DynamicArray(unsigned size);
		~DynamicArray();

		T* m_pData;
	};

	template<class T>
	Leviathan::DynamicArray<T>::DynamicArray(unsigned size)
	{
		m_pData = (T*)malloc(size);
	}

	template<class T>
	Leviathan::DynamicArray<T>::~DynamicArray()
	{
		free(m_pData);
	}
}
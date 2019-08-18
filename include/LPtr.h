#pragma once
#include <memory>
#include "GlobalDef.h"

namespace Leviathan
{
	template <class T>
	class LPtr
	{
	public:
		LPtr(T* pointer);
		LPtr(const std::shared_ptr<T>& ref) : m_lPtr(ref) {}
		LPtr() : LPtr(nullptr) {};

		LPtr(const LPtr<T>& rhs);
		LPtr(const LPtr<T>&& rhs);
		~LPtr();
		
		LPtr<T>& operator=(const LPtr<T>& rhs);
		std::shared_ptr<T> operator->() const;
		T& operator*() const;

		T* Get() const;
		void Reset(const LPtr<T>& rhs);
		
		bool operator==(const LPtr<T>& rhs) const;
		bool operator!=(const LPtr<T>& rhs) const;
		bool operator!=(T* rhs) const;

		template <typename N>
		LPtr<N> To();

		operator bool();

	private:
		std::shared_ptr<T> m_lPtr;
	};

	template <class T>
	bool LPtr<T>::operator!=(T* rhs) const
	{
		return m_lPtr.get() != rhs;
	}

	template <class T>
	template <typename N>
	LPtr<N> LPtr<T>::To()
	{
		std::shared_ptr<N> convert_pointer = std::dynamic_pointer_cast<N, T>(m_lPtr);
		return LPtr<N>(convert_pointer);
	}

	template <class T>
	LPtr<T>::LPtr(const LPtr<T>&& rhs)
	{
		Reset(rhs);
	}

	template <class T>
	void LPtr<T>::Reset(const LPtr<T>& rhs)
	{
		m_lPtr= rhs.m_lPtr;
	}

	template <class T>
	bool LPtr<T>::operator!=(const LPtr<T>& rhs) const
	{
		return !(*this == rhs);
	}

	template <class T>
	T* LPtr<T>::Get() const
	{
		return m_lPtr.get();
	}

	template <class T>
	T& LPtr<T>::operator*() const
	{
		return *m_lPtr;
	}

	template <class T>
	bool LPtr<T>::operator==(const LPtr<T>& rhs) const
	{
		return m_lPtr == rhs.m_lPtr;
	}

	template <class T>
	LPtr<T>::operator bool()
	{
		return m_lPtr != nullptr;
	}

	template <class T>
	LPtr<T>::~LPtr() = default;

	template <class T>
	std::shared_ptr<T> LPtr<T>::operator->() const
	{
		return m_lPtr;
	}

	template <class T>
	LPtr<T>::LPtr(const LPtr<T>& rhs)
	{
		Reset(rhs);
	}

	template <class T>
	LPtr<T>& LPtr<T>::operator=(const LPtr<T>& rhs)
	{
		Reset(rhs);
		return *this;
	}

	template <class T>
	LPtr<T>::LPtr(T* pointer)
	{
		m_lPtr = std::shared_ptr<T>(pointer);
	}

	template<class T, class N>
	LPtr<N> TryCast(LPtr<T> lPtr)
	{
		return lPtr.To<N>();
	}
}
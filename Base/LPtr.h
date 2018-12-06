#pragma once
#include <memory>
#include "GlobalDef.h"

namespace Leviathan
{
	template <class T>
	class LPtr
	{
	public:
		template<class T, class N>
		friend LPtr<N> TryCast(LPtr<T> lPtr);

		LPtr(T* pointer);
		LPtr() : LPtr(nullptr) {};
		LPtr(const LPtr<T>& rhs);
		~LPtr();
		
		LPtr<T>& operator=(const LPtr<T>& rhs);
		std::shared_ptr<T> operator->() const;
		T& operator*() const;

		T* get() const;
		void reset(const LPtr<T>& rhs);
		
		bool operator==(const LPtr<T>& rhs) const;
		bool operator!=(const LPtr<T>& rhs) const;
		bool operator!=(T* rhs) const;
		operator bool();

	private:
		
		bool _setPointer(const LPtr<T>& rhs);
		std::shared_ptr<T> m_lPtr;
	};

	template <class T>
	bool Leviathan::LPtr<T>::operator!=(T* rhs) const
	{
		return m_lPtr.get() != rhs;
	}

	template <class T>
	void Leviathan::LPtr<T>::reset(const LPtr<T>& rhs)
	{
		m_lPtr = rhs.m_lPtr;
	}

	template <class T>
	bool Leviathan::LPtr<T>::operator!=(const LPtr<T>& rhs) const
	{
		return !(*this == rhs);
	}

	template <class T>
	T* Leviathan::LPtr<T>::get() const
	{
		return m_lPtr.get();
	}

	template <class T>
	T& Leviathan::LPtr<T>::operator*() const
	{
		return *m_lPtr;
	}

	template <class T>
	bool Leviathan::LPtr<T>::operator==(const LPtr<T>& rhs) const
	{
		return m_lPtr == rhs.m_lPtr;
	}

	template <class T>
	Leviathan::LPtr<T>::operator bool()
	{
		return (m_lPtr != nullptr);
	}

	template <class T>
	Leviathan::LPtr<T>::~LPtr()
	{
		LeviathanOutStream << "[INFO] LPtr destroy." << std::endl;
	}

	template <class T>
	std::shared_ptr<T> LPtr<T>::operator->() const
	{
		return m_lPtr;
	}

	template <class T>
	bool LPtr<T>::_setPointer(const LPtr<T>& rhs)
	{
		if (!rhs.m_lPtr)
		{
			return false;
		}

		m_lPtr = rhs.m_lPtr;
		return true;
	}

	template <class T>
	LPtr<T>::LPtr(const LPtr<T>& rhs)
	{
		_setPointer(rhs);
	}

	template <class T>
	LPtr<T>& LPtr<T>::operator=(const LPtr<T>& rhs)
	{
		_setPointer(rhs);
		return *this;
	}

	template <class T>
	LPtr<T>::LPtr(T* pointer)
	{
		if (!pointer)
		{
			LeviathanOutStream << "[ERROR] nullptr set." << std::endl;
		}

		m_lPtr = std::shared_ptr<T>(pointer);
	}

	template<class T, class N>
	LPtr<N> TryCast(LPtr<T> lPtr)
	{
		if (!lPtr.m_lPtr)
		{
			LeviathanOutStream << "[ERROR] Nullptr need not convert." << std::endl;
			return nullptr;
		}

		LPtr<N> result;
		result.m_lPtr = lPtr.m_lPtr;

		return result;
	}
}
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
		LPtr(const LPtr<T>& rhs);
		~LPtr();
		
		LPtr<T>& operator=(const LPtr<T>& rhs);
		std::shared_ptr<T> operator->();

		bool operator==(const LPtr<T>& rhs);
		operator bool();

	private:
		LPtr() {};
		bool _setPointer(const LPtr<T>& rhs);
		std::shared_ptr<T> m_lPtr;
	};

	template <class T>
	bool Leviathan::LPtr<T>::operator==(const LPtr<T>& rhs)
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
		LeviathanOutStream << "LPtr destroy." << std::endl;
	}

	template <class T>
	std::shared_ptr<T> LPtr<T>::operator->()
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
		auto sharedPointer = lPtr.m_lPtr;
		if (!sharedPointer)
		{
			LeviathanOutStream << "[ERROR] Nullptr need not convert." << std::endl;
			return nullptr;
		}

		LPtr<N> result = LPtr<N>();
		result.m_lPtr = sharedPointer;

		return result;
	}
}
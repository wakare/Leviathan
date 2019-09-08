#pragma once
#include <memory>
#include <utility>
#include "GlobalDef.h"

namespace Leviathan
{
	template <class T>
	class LSPtr
	{
	public:
		LSPtr(T* pointer);
		LSPtr(std::shared_ptr<T> ref) : m_ptr(std::move(ref)) {}
		LSPtr() : LSPtr(nullptr) {};

		LSPtr(const LSPtr<T>& rhs);
		LSPtr(const LSPtr<T>&& rhs) noexcept;
		~LSPtr();
		
		LSPtr<T>& operator=(const LSPtr<T>& rhs);
		std::shared_ptr<T> operator->() const;
		T& operator*() const;

		T* Get() const;
		void Reset(const LSPtr<T>& rhs);
		
		bool operator==(const LSPtr<T>& rhs) const;
		bool operator!=(const LSPtr<T>& rhs) const;
		bool operator!=(T* rhs) const;

		template <typename N>
		LSPtr<N> To() const;

		operator bool();

	private:
		std::shared_ptr<T> m_ptr;
	};

	template <class T>
	bool LSPtr<T>::operator!=(T* rhs) const
	{
		return m_ptr.get() != rhs;
	}

	template <class T>
	template <typename N>
	LSPtr<N> LSPtr<T>::To() const
	{
		std::shared_ptr<N> convert_pointer = std::dynamic_pointer_cast<N, T>(m_ptr);
		return LSPtr<N>(convert_pointer);
	}

	template <class T>
	LSPtr<T>::LSPtr(const LSPtr<T>&& rhs) noexcept
	{
		Reset(rhs);
	}

	template <class T>
	void LSPtr<T>::Reset(const LSPtr<T>& rhs)
	{
		m_ptr= rhs.m_ptr;
	}

	template <class T>
	bool LSPtr<T>::operator!=(const LSPtr<T>& rhs) const
	{
		return !(*this == rhs);
	}

	template <class T>
	T* LSPtr<T>::Get() const
	{
		return m_ptr.get();
	}

	template <class T>
	T& LSPtr<T>::operator*() const
	{
		return *m_ptr;
	}

	template <class T>
	bool LSPtr<T>::operator==(const LSPtr<T>& rhs) const
	{
		return m_ptr == rhs.m_ptr;
	}

	template <class T>
	LSPtr<T>::operator bool()
	{
		return m_ptr != nullptr;
	}

	template <class T>
	LSPtr<T>::~LSPtr() = default;

	template <class T>
	std::shared_ptr<T> LSPtr<T>::operator->() const
	{
		return m_ptr;
	}

	template <class T>
	LSPtr<T>::LSPtr(const LSPtr<T>& rhs)
	{
		Reset(rhs);
	}

	template <class T>
	LSPtr<T>& LSPtr<T>::operator=(const LSPtr<T>& rhs)
	{
		Reset(rhs);
		return *this;
	}

	template <class T>
	LSPtr<T>::LSPtr(T* pointer)
	{
		m_ptr = std::shared_ptr<T>(pointer);
	}

	template<class T, class N>
	LSPtr<N> TryCast(LSPtr<T> lPtr)
	{
		return lPtr.To<N>();
	}
}
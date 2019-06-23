#pragma once
#include "RuntimeAttribute.h"
#include <sstream>

namespace Util
{
	template <typename T>
	class InternalAttribute : public RuntimeAttribute
	{
	public:
		InternalAttribute(T value);
		void SetName(const INTERN_STRING& name);
		void SetDesc(const INTERN_STRING& desc);
		void SetValue(const INTERN_STRING& value);

		INTERN_STRING GetDesc() const;
		INTERN_STRING GetName() const;
		INTERN_STRING GetValue() const;

	private:
		T m_value;
		INTERN_STRING m_name;
		INTERN_STRING m_desc;
	};

	template<typename T>
	inline InternalAttribute<T>::InternalAttribute(T value)
		: m_value(value)
		, m_desc(INTERN_STRING("Default desc."))
	{
	}

	template <typename T>
	void Util::InternalAttribute<T>::SetDesc(const INTERN_STRING& desc)
	{
		m_desc = desc;
	}

	template <typename T>
	void Util::InternalAttribute<T>::SetName(const INTERN_STRING& name)
	{
		m_name = name;
	}

	template<typename T>
	inline void InternalAttribute<T>::SetValue(const INTERN_STRING & value)
	{
		std::stringstream stream(value);
		stream >> m_value;
	}

	template<typename T>
	inline INTERN_STRING InternalAttribute<T>::GetDesc() const
	{
		return m_desc;
	}

	template <typename T>
	INTERN_STRING Util::InternalAttribute<T>::GetName() const
	{
		return m_name;
	}

	template<typename T>
	inline INTERN_STRING InternalAttribute<T>::GetValue() const
	{
		// TODO: Use internal defined value-stirng convert interface.
		return std::to_string(m_value);
	}

	
	// Base internal typedef
	typedef InternalAttribute<int> AttributeInt;
	typedef InternalAttribute<long> AttributeLong;
	typedef InternalAttribute<unsigned> AttributeUInt;
	typedef InternalAttribute<float> AttributeFloat;
	typedef InternalAttribute<double> AttributeDouble;
}
#pragma once

#include <string>
#include "UniqueIdDispatcher.h"

namespace Util
{
	typedef std::string INTERN_STRING;

	/*
		RuntimeAttribute is a base class for user to extend their custom attribute.

		RuntimeAttribute has two base component:
			0. Value
			1. Name
			2. Description

		Description is alternative parameter, just for indicating user
		Value must be set, and it can be parse from user input (string)
		Name is key for user searching attribute
	*/

	class RuntimeAttribute;

	typedef UniqueIdDispatcher<RuntimeAttribute> IdDispatcher;
	IdDispatcher* IdDispatcher::g_instance = nullptr;

	class RuntimeAttribute
	{
	public:
		RuntimeAttribute();
		RuntimeAttribute(const RuntimeAttribute& lhs) = delete;
		RuntimeAttribute(const RuntimeAttribute&& lhs) = delete;

		unsigned GetId() const;

		virtual void SetValue(const INTERN_STRING& value) = 0;
		virtual void SetName(const INTERN_STRING& name) = 0;
		virtual void SetDesc(const INTERN_STRING& desc) = 0;

		virtual INTERN_STRING GetValue() const = 0;
		virtual INTERN_STRING GetName() const = 0;
		virtual INTERN_STRING GetDesc() const = 0;
		
	private:
		unsigned m_attribute_id;
	};

	inline RuntimeAttribute::RuntimeAttribute()
	{
		m_attribute_id = IdDispatcher::Instance().GetCurrentIdAndIncrement();
	}

	inline unsigned RuntimeAttribute::GetId() const
	{
		return m_attribute_id;
	}

}
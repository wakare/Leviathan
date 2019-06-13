#include <iostream>

#include "RuntimeAttributeWatcher.h"
#include "InternRuntimeAttribute.h"

using namespace Util;

int main()
{
	RuntimeAttributeWatcher watcher;

	std::unique_ptr<RuntimeAttribute> m_attribute_int;
	std::unique_ptr<RuntimeAttribute> m_attribute_unsigned;
	std::unique_ptr<RuntimeAttribute> m_attribute_float;
	std::unique_ptr<RuntimeAttribute> m_attribute_double;

	m_attribute_int.reset(new AttributeInt(10));
	m_attribute_int->SetName("TEST_ATTRIBUTE_INT");
	m_attribute_int->SetValue("999");

	m_attribute_unsigned.reset(new AttributeUInt(10));
	m_attribute_unsigned->SetName("TEST_ATTRIBUTE_UINT");
	m_attribute_unsigned->SetValue("999");

	m_attribute_float.reset(new AttributeFloat(10));
	m_attribute_float->SetName("TEST_ATTRIBUTE_FLOAT");
	m_attribute_float->SetValue("1e10f");

	m_attribute_double.reset(new AttributeDouble(10));
	m_attribute_double->SetName("TEST_ATTRIBUTE_DOUBLE");
	m_attribute_double->SetValue("999.99999");

	watcher.Register(std::move(m_attribute_int));
	watcher.Register(std::move(m_attribute_unsigned));
	watcher.Register(std::move(m_attribute_float));
	watcher.Register(std::move(m_attribute_double));
	
	return 0;
}
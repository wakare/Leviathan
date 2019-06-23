#include "CommandView.h"
#include "RuntimeAttribute.h"
#include "InternRuntimeAttribute.h"

using namespace Util;

class AttributeCustom : public RuntimeAttribute
{
public:
	virtual void SetValue(const INTERN_STRING& value)
	{
		m_data = value;
	}

	virtual void SetName(const INTERN_STRING& name)
	{
		m_name = name;
	}

	virtual void SetDesc(const INTERN_STRING& desc)
	{
		m_desc = desc;
	}

	virtual INTERN_STRING GetValue() const
	{
		return m_data;
	}

	virtual INTERN_STRING GetName() const
	{
		return m_name;
	}

	virtual INTERN_STRING GetDesc() const
	{
		return m_desc;
	}

private:
	std::string m_data;
	std::string m_name;
	std::string m_desc;
};

int main()
{
	CommandView view(0, nullptr);
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

	view.RegisterAttribute(std::move(m_attribute_int));
	view.RegisterAttribute(std::move(m_attribute_unsigned));
	view.RegisterAttribute(std::move(m_attribute_float));
	view.RegisterAttribute(std::move(m_attribute_double));

	std::unique_ptr<RuntimeAttribute> custome_attribute;
	custome_attribute.reset(new AttributeCustom);
	custome_attribute->SetName("CUSTOM_ATTRIBUTE");
	custome_attribute->SetValue("114514");
	custome_attribute->SetDesc("This is a desc");

	view.RegisterAttribute(std::move(custome_attribute));

	view.Run();

	return 0;
}
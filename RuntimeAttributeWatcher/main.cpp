#include <iostream>

#include "RuntimeAttributeWatcher.h"
#include "InternRuntimeAttribute.h"

using namespace Util;

std::string& trim(std::string &s)
{
	if (s.empty())
	{
		return s;
	}

	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

bool _processAssignment(const std::string& source, RuntimeAttributeWatcher& watcher)
{
	auto equal_symbol_position = source.find_last_of('=');
	if (equal_symbol_position == std::string::npos)
	{
		return false;
	}

	std::string left_string = source.substr(0, equal_symbol_position);
	std::string right_string = source.substr(equal_symbol_position + 1);

	trim(left_string);
	trim(right_string);

	auto second_equal_symbol_position = left_string.find_last_of('=');
	if (second_equal_symbol_position == std::string::npos)
	{
		auto _matched = [right_string](RuntimeAttribute& attribute) 
		{
			attribute.SetValue(right_string);
		};

		watcher.MatchOne(left_string, _matched);
		return true;
	}

	return false;
}

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

	auto _matched = [](RuntimeAttribute& attribute) 
	{
		std::cout << "Attribute Name: " << attribute.GetName() << " , Attribute Value: " << attribute.GetValue() << " , Attribute Desc: " << attribute.GetDesc() << std::endl;
	};

	auto _searched = [](RuntimeAttribute& attribute) 
	{
		std::cout << "Attribute:" << attribute.GetName() << " has Searched!" << std::endl;
	};

	bool exit = false;
	char input_buffer[100];

	memset(input_buffer, 0, sizeof(input_buffer));
	size_t buf_pointer = 0;

	std::cout << std::endl << "Please input varaible name:" << std::endl;

	while (!exit)
	{
		char current_input_char;
		//std::cin.get(current_input_char);
		current_input_char = getchar();

		bool is_regular_char = current_input_char != '\n' &&current_input_char != '\t';
		if (is_regular_char)
		{
			input_buffer[buf_pointer++] = current_input_char;
			continue;
		}

		input_buffer[buf_pointer] = 0;
		std::string line = input_buffer;
		memset(input_buffer, 0, sizeof(input_buffer));
		buf_pointer = 0;

		std::cout << "Current input string is " << line << std::endl;

		if (line.size() == 0)
		{
			std::cout << "Input string is empty." << std::endl;
			continue;
		}

		// First, do regex_match
		bool has_matched = watcher.MatchOne(line, _matched);
		if (has_matched)
		{
			continue;
		}

		std::cout << "No Attribute has matched, try to search other attribute." << std::endl;
		bool has_searched = watcher.SearchAll(line, _searched);

		if (has_searched)
		{
			continue;
		}

		// Maybe this statement is a assignment string
		if (_processAssignment(line, watcher))
		{
			continue;
		}

		std::cout << "No Attribute has searched, please use . to find all attribute." << std::endl;
	}
	
	return 0;
}
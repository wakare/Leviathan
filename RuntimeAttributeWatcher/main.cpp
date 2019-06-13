#include <conio.h>
#include <iostream>
#include <vector>

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

void _clearCurrentLine()
{
	std::cout << "\r                                                                                                             \r";
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
	size_t buf_pointer = 0;

	auto _clear_input_buf = [&]()
	{
		buf_pointer = 0;
		memset(input_buffer, 0, sizeof(input_buffer));
	};

	std::cout << "Please input varaible name:" << std::endl;

	bool during_tab = false;
	unsigned tab_index = 0;
	std::vector<std::string> backup_select_items;

	auto _clear_tab_objects = [&]() 
	{
		during_tab = false;
		tab_index = 0;
		backup_select_items.clear();
	};

	while (!exit)
	{
		char current_input_char;
		//std::cin.get(current_input_char);
		current_input_char = _getch();
		std::cout << current_input_char;

		bool is_regular_char = current_input_char != '\r' &&current_input_char != '\t';
		if (is_regular_char)
		{
			_clear_tab_objects();
			input_buffer[buf_pointer++] = current_input_char;
			input_buffer[buf_pointer] = 0;
			continue;
		}

		if (current_input_char == '\t')
		{
			_clearCurrentLine();

			if (!during_tab)
			{
				during_tab = true;
				auto _searched = [&backup_select_items](RuntimeAttribute& attribute)
				{
					backup_select_items.push_back(attribute.GetName());
				};

				std::string current_search_string = input_buffer;
				watcher.SearchAll(current_search_string, _searched);	
			}
			else
			{

			}

			if (backup_select_items.size() != 0)
			{
				auto& tab_string = backup_select_items[tab_index];

				tab_index = (tab_index + 1) % backup_select_items.size();

				_clear_input_buf();
				memcpy(input_buffer, tab_string.c_str(), tab_string.size());
				buf_pointer = tab_string.size();

				_clearCurrentLine();
				std::cout << tab_string;
			}

			continue;
		}

		else if (current_input_char == '\r')
		{
			_clearCurrentLine();
		}

		input_buffer[buf_pointer] = 0;
		std::string line = input_buffer;
		std::cout << "Current input string is " << line << std::endl;

		_clear_input_buf();
		
		_clear_tab_objects();
		
		bool has_searched = false;
		bool has_matched = false;
		
		if (line.size() == 0)
		{
			std::cout << "Input string is empty." << std::endl;
			goto ExitSuccess;
		}

		// First, do regex_match
		has_matched = watcher.MatchOne(line, _matched);
		if (has_matched)
		{
			goto ExitSuccess;
		}

		std::cout << "No Attribute has matched, try to search other attribute." << std::endl;
		has_searched = watcher.SearchAll(line, _searched);

		if (has_searched)
		{
			goto ExitSuccess;
		}

		// Maybe this statement is a assignment string
		if (_processAssignment(line, watcher))
		{
			goto ExitSuccess;
		}

		std::cout << "No Attribute has searched, please use . to find all attribute." << std::endl;
		goto Loop;

	ExitSuccess:
		std::cout << "Please input varaible name:" << std::endl;

	Loop:
		continue;
	}
	
	return 0;
}
#include <iostream>
#include <vector>
#include <string>

#include <conio.h>

#include "CommandView.h"
#include "InternRuntimeAttribute.h"

namespace Util
{
	/*
		Intern util function
	*/
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
		// TODO: finish consistant assignment
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

	CommandView::CommandView(int argc, char** argv)
		: m_exit(false)
		, m_buf_pointer(0)
	{
		// Register tab callback
		RegisterTokenCallback(ECT_TAB, std::bind(&BestMatchHelper::Apply, &match_helper, std::placeholders::_1));
		RegisterNonTokenCallback(ECT_TAB, std::bind(&BestMatchHelper::UnApply, &match_helper, std::placeholders::_1));

		RegisterTokenCallback(ECT_ENTER, [this](CommandView&) 
			{
				_clearCurrentLine(); 
				return true; 
			});

		RegisterTokenCallback(ECT_BACKSPACE, [this](CommandView&) 
			{
				if (m_buf_pointer > 0)
				{
					m_input_buffer[m_buf_pointer] = 0;
					m_input_buffer[--m_buf_pointer] = 0;
					_clearCurrentLine();
					_print_current_input();
				}

				return false;
			});
	}

	void CommandView::RegisterTokenCallback(CONTROL_TOKEN token, token_callback callback)
	{
		m_token_callback[token] = callback;
	}

	void CommandView::RegisterNonTokenCallback(CONTROL_TOKEN token, token_callback callback)
	{
		m_nontoken_callback[token] = callback;
	}

	void CommandView::RegisterAttribute(std::unique_ptr<RuntimeAttribute> attribute)
	{
		m_watcher.Register(std::move(attribute));
	}

	void CommandView::Run()
	{
		auto _matched = [](RuntimeAttribute& attribute)
		{
			std::cout << "Attribute Name: " << attribute.GetName() << " , Attribute Value: " << attribute.GetValue() << " , Attribute Desc: " << attribute.GetDesc() << std::endl;
		};

		auto _searched = [](RuntimeAttribute& attribute)
		{
			std::cout << "Attribute:" << attribute.GetName() << " has Searched!" << std::endl;
		};

		std::cout << "Please input varaible name: " << std::endl;

		while (!m_exit)
		{
			int current_input_char;
			current_input_char = _getch();

			bool is_regular_char = (' ' <= current_input_char && current_input_char <= 'z');
			if (is_regular_char)
			{
				for (auto& callback : m_nontoken_callback)
				{
					callback.second(*this);
				}

				std::cout << static_cast<char>(current_input_char);

				m_input_buffer[m_buf_pointer++] = current_input_char;
				m_input_buffer[m_buf_pointer] = 0;
				continue;
			}

			auto temp_it = m_nontoken_callback.begin();
			while (temp_it != m_nontoken_callback.end())
			{
				if (temp_it->first != current_input_char)
				{
					temp_it->second(*this);
				}

				temp_it++;
			}

			auto it = m_token_callback.find(static_cast<CONTROL_TOKEN>(current_input_char));
			if (it == m_token_callback.end())
			{
				std::cout << "Enter invalid character: " << current_input_char << std::endl;
				continue;
			}

			if (!it->second(*this))
			{
				continue;
			}

			m_input_buffer[m_buf_pointer] = 0;
			std::string line = m_input_buffer;
			std::cout << "Current input string is " << line << std::endl;

			_clear_input_buf();
			bool has_searched = false;
			bool has_matched = false;

			if (line.size() == 0)
			{
				std::cout << "Input string is empty." << std::endl;
				goto ExitSuccess;
			}

			// First, do regex_match
			has_matched = m_watcher.MatchOne(line, _matched);
			if (has_matched)
			{
				goto ExitSuccess;
			}

			std::cout << "No Attribute has matched, try to search other attribute." << std::endl;
			has_searched = m_watcher.SearchAll(line, _searched);

			if (has_searched)
			{
				goto ExitSuccess;
			}

			// Maybe this statement is a assignment string
			if (_processAssignment(line, m_watcher))
			{
				goto ExitSuccess;
			}

			std::cout << "No Attribute has searched, please use . to find all attribute." << std::endl;
			goto Loop;

		ExitSuccess:
			std::cout << "\nPlease input varaible name:" << std::endl;

		Loop:
			continue;
		}
	}

	void CommandView::SetExit()
	{
		m_exit = true;
	}

	void CommandView::GetInputBufferData(char*& input_buffer, size_t& buf_pointer)
	{
		input_buffer = m_input_buffer;
		buf_pointer = m_buf_pointer;
	}

	void CommandView::SetInputBufferData(const char* input_buffer, size_t buffer_size)
	{
		_clear_input_buf();
		memcpy(m_input_buffer, input_buffer, buffer_size);
		m_buf_pointer = buffer_size - 1;
	}

	RuntimeAttributeWatcher & CommandView::GetWatcher()
	{
		return m_watcher;
	}

	size_t CommandView::GetInputBufferMaxSize() const
	{
		return 100;
	}

	void CommandView::_clearCurrentLine()
	{
		std::cout << "\r                                                                                                 \r";
	}

	void CommandView::_clear_input_buf()
	{
		m_buf_pointer = 0;
		memset(m_input_buffer, 0, sizeof(m_input_buffer));
	}

	void CommandView::_print_current_input()
	{
		std::cout << m_input_buffer;
	}

	BestMatchHelper::BestMatchHelper()
		: during_tab(false)
		, tab_index(0)
	{

	}

	bool BestMatchHelper::Apply(CommandView& view)
	{
		if (!during_tab)
		{
			during_tab = true;
			auto _searched = [this](RuntimeAttribute& attribute)
			{
				backup_select_items.push_back(attribute.GetName());
			};

			char* current_input_buffer = nullptr;
			size_t current_buf_pointer = 0;
			view.GetInputBufferData(current_input_buffer, current_buf_pointer);

			std::string current_search_string = current_input_buffer;
			view.GetWatcher().SearchAll(current_search_string, _searched);
		}

		view._clearCurrentLine();
		view._clear_input_buf();

		if (backup_select_items.size() != 0)
		{
			auto& tab_string = backup_select_items[tab_index];
			assert(tab_string.size() < view.GetInputBufferMaxSize());

			tab_index = (tab_index + 1) % backup_select_items.size();

			// TODO: May be exist bug
			char temp_buf[100]; memset(temp_buf, 0, sizeof(temp_buf));

			memcpy(temp_buf, tab_string.c_str(), tab_string.size());
			view.SetInputBufferData(temp_buf, tab_string.size() + 1);

			/*view._clearCurrentLine();*/
			view._print_current_input();
		}

		return false;
	}

	bool BestMatchHelper::UnApply(CommandView& view)
	{
		_clear_tab_objects();
		return false;
	}

	void BestMatchHelper::_clear_tab_objects()
	{
		if (during_tab)
		{
			during_tab = false;
			tab_index = 0;
			backup_select_items.clear();
		}
	}

}
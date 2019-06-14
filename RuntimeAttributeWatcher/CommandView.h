#pragma once

#include <map>
#include <vector>
#include <memory>
#include <functional>
#include "RuntimeAttribute.h"
#include "RuntimeAttributeWatcher.h"
#include <assert.h>

namespace Util
{
	class CommandView;

	enum CONTROL_TOKEN
	{
		ECT_TAB = '\t',
		ECT_ENTER = '\r',
		ECT_BACKSPACE = 8,
	};

	// Tool class
	class BestMatchHelper
	{
	public:
		BestMatchHelper();

		bool Apply(CommandView& view);
		bool UnApply(CommandView& view);

	private:
		void _clear_tab_objects();

		bool during_tab;
		unsigned tab_index;
		std::vector<std::string> backup_select_items;
	};

	/*
		This class is used for RuntimeAttributeWatcher in console.
		Interact with standard stream (std::cin & std::cout)
	*/
	class CommandView
	{
	public:
		CommandView(int argc, char** argv);
		CommandView(CommandView& lhs) = delete;
		CommandView(CommandView&& lhs) = delete;

		/*
			return value indicate whether do next logic.		
		*/
		typedef std::function<bool(CommandView& view)> token_callback;
		void RegisterTokenCallback(CONTROL_TOKEN token, token_callback callback);
		void RegisterNonTokenCallback(CONTROL_TOKEN token, token_callback callback);
		
		void RegisterAttribute(std::unique_ptr<RuntimeAttribute> attribute);

		void Run();
		void SetExit();

		void GetInputBufferData(char*& input_buffer, size_t& buf_pointer);

		// last char must be 0
		void SetInputBufferData(const char* input_buffer, size_t buffer_size);
		RuntimeAttributeWatcher& GetWatcher();
		
		size_t GetInputBufferMaxSize() const;

		void _clearCurrentLine();
		void _clear_input_buf();
		void _print_current_input();

	private:
		std::map<CONTROL_TOKEN, token_callback> m_token_callback;
		std::map<CONTROL_TOKEN, token_callback> m_nontoken_callback;
		RuntimeAttributeWatcher m_watcher;

		// Runtime data
		BestMatchHelper match_helper;

		bool m_exit;
		char m_input_buffer[100];
		size_t m_buf_pointer;
	};
}


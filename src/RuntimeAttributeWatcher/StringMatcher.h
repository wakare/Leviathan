#pragma once
#include <string>

namespace Util
{
	class StringMatcher
	{
	public:
		static bool Match(const std::string& source, const std::string& pattern);
		static bool Search(const std::string& source, const std::string& pattern);
	};
}
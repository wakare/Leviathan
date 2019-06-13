#include "StringMatcher.h"
#include <regex>

namespace Util
{
	bool StringMatcher::Match(const std::string& source, const std::string& pattern)
	{
		return std::regex_match(source, std::regex(pattern));
	}

	bool StringMatcher::Search(const std::string & source, const std::string & pattern)
	{
		return std::regex_search(source, std::regex(pattern));
	}
}
#pragma once
#include <iostream>
#include <stdarg.h>

class KLog
{
public:
	static void Log(const std::string& s)
	{
		std::cout << s.c_str() << std::endl;
	}

	static void Log(const char *s)
	{
		std::cout << s << std::endl;
	}

	//static void LogFormat(const char* s, ...)
	//{
	//	// TODO : Find a better way to determine the length.
	//	constexpr unsigned uMaxLength = 200;

	//	va_list list;
	//	va_start(list, s);

	//	

	//	char buffer[uMaxLength];
	//	snprintf(buffer, uMaxLength, s, ...);
	//}
};
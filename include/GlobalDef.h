#pragma once
#include <iostream>

namespace Leviathan
{
	#define LeviathanInStream std::cin
	#define LeviathanOutStream std::cout
	#define LogLine(s) LeviathanOutStream << s << std::endl;

	#define PI_DOUBLE 3.141592653589793
	#define PI_FLOAT 3.1415927f
	#define ANGLE_TO_RADIAN(angle) ((angle) / PI_DOUBLE)

	#define EXIT_IF_FALSE(statement) { if (!(statement)) { LogLine("[ERROR] Condition:" << #statement << " is false."); return false;}}
	#define RAND_NUM_ZERO_TO_ONE ((float)(rand()) / RAND_MAX)

	enum EventType
	{
		INPUT_EVENT,
		USER_EVENT,
	};
}
#pragma once
#include <iostream>
#include <functional>
#include <assert.h>

namespace Leviathan
{
	#define LeviathanInStream std::cin
	#define LeviathanOutStream std::cout
	#define LogLine(s) LeviathanOutStream << s << std::endl;

	#define PI_DOUBLE 3.141592653589793
	#define PI_FLOAT 3.1415927f
	#define ANGLE_TO_RADIAN(angle) ((angle) / PI_DOUBLE)

	#define EXIT_IF_FALSE(statement) { if (!(statement)) { assert(false); LogLine("[ERROR] Condition:" << #statement << " is false."); return false;}}
	#define RAND_FLOAT_ZERO_TO_ONE ((float)(rand()) / RAND_MAX)

	enum EventType
	{
		INPUT_EVENT,
		USER_EVENT,
	};

	enum AppState
	{
		EAS_UNINITED,
		EAS_INITING,
		EAS_INITED,
		EAS_RUNNING,
		EAS_STOPPING,
		EAS_STOPPED
	};

	typedef std::function<void(void)> SceneDataRequestFunc;
}
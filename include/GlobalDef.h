#pragma once
#include <iostream>
#include <functional>
#include <assert.h>
#include <fstream>

namespace Leviathan
{
	// Log file stream
	static std::ofstream g_levLogFile("Leviathan.log", std::ios::out);

	#define LeviathanInStream std::cin
	#define LeviathanOutStream Leviathan::g_levLogFile
	#define LogLine(s) LeviathanOutStream << s << std::endl;

	#define PI_DOUBLE 3.141592653589793
	#define PI_FLOAT 3.1415927f
	#define ANGLE_TO_RADIAN(angle) ((angle) / PI_DOUBLE)

	#define EXIT_IF_FALSE(statement) { if (!(statement)) { /*assert(false);*/ LogLine("[ERROR] Condition:" << #statement << " is false."); return false;}}
	#define RAND_FLOAT_ZERO_TO_ONE ((float)(rand()) / RAND_MAX)
	#define  LEV_ASSERT(a) assert((a))

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

	enum LevSceneType
	{
		ELST_3D_SCENE,
		ELST_UNKNOWN
	};

	enum LevRendererType
	{
		ELRT_OPENGL,
		ELRT_UNKNOWN
	};

	enum LevSceneObjectDescType
	{
		ELSOD_MESH = 1,
		ELSOD_MATHEMATIC = 2,
	};

	typedef std::function<void(void)> SceneDataRequestFunc;
}
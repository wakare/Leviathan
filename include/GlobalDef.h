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
	//#define LeviathanOutStream Leviathan::g_levLogFile
	#define LeviathanOutStream std::cout
	#define LogLine(s) LeviathanOutStream << s << std::endl;

	#define PI_DOUBLE 3.141592653589793
	#define PI_FLOAT 3.1415927f
	#define ANGLE_TO_RADIAN(angle) ((angle * PI_DOUBLE)  / 180.0f)

	#define EXIT_IF_FALSE(statement) { if (!(statement)) { /*assert(false);*/ LogLine("[ERROR] Condition:" << #statement << " is false."); return false;}}
	#define RAND_FLOAT_ZERO_TO_ONE ((float)(rand()) / RAND_MAX)
	#define LEV_ASSERT(a) assert((a))

	#define NON_COPY_CONSTRUCTION(className)	className(const className& rhs) = delete;
	#define NON_COPY_ASSIGNMENT(className)		className& operator=(const className& rhs) = delete;

	#define NON_COPY(className) \
			NON_COPY_CONSTRUCTION(className) \
			NON_COPY_ASSIGNMENT(className) \

	#define NON_MOVE_CONSTRUCTION(className)	className(const className&& rhs) = delete;
	#define NON_MOVE_ASSIGNMENT(className)		className& operator=(const className&& rhs) = delete;

	#define NON_MOVE(className) \
			NON_MOVE_CONSTRUCTION(className) \
			NON_MOVE_ASSIGNMENT(className) \

	#define UNIQUE_INSTANCE(className) \
			NON_COPY(className)\
			NON_MOVE(className)\
	
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
		ELSOD_MESH_TRIANGLE = 1,
		ELSOD_MESH_POINT = 2,
		ELSOD_MESH_LINE = 3,
		ELSOD_MATHEMATIC = 1024,
	};

	enum LevFileType
	{
		EFT_REGULAR_FILE,
		EFT_DIR_FILE
	};

	// RAII Array
	class RAIIBufferData
	{
	public:
		RAIIBufferData(unsigned byteSize) : m_byte_size(byteSize) { m_data = malloc(byteSize); };
		~RAIIBufferData() { if (m_data) { free(m_data); m_data = nullptr; } };

		void SetArrayData(const void* data, unsigned dataSize) { memcpy(m_data, data, dataSize); };
		void* GetArrayData() { return m_data; }
		const void* GetArrayData() const { return m_data; }

		unsigned GetArrayDataByteSize() const { return m_byte_size; }

	private:
		unsigned m_byte_size;
		void* m_data;
	};

	typedef std::function<void(void)> SceneDataRequestFunc;
}
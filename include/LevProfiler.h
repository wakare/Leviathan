#pragma once
#include <mutex>
#include <windows.h>
#include <iostream>

class LevProfiler
{
public:
	static LevProfiler* Instance()
	{
		static std::once_flag _flag;
		std::call_once(_flag, []() { g_instance = new LevProfiler(); });

		return g_instance;
	}

	void Reset()
	{
		m_lastTickTime = 0;
		std::cout << "[Profile] Profile reset." << std::endl;
	}

	void Tick()
	{
		if (m_lastTickTime > 0)
		{
			std::cout << "[Profile] Cost time: " << GetTickCount64() - m_lastTickTime << " ms." << std::endl;
			m_lastTickTime = 0;
			return;
		}

		else
		{
			std::cout << "[Profile] Begin profile." << std::endl;
			m_lastTickTime = GetTickCount64();
		}
	}

private:
	LevProfiler(): m_lastTickTime(0) {};
	~LevProfiler() { if (g_instance) delete g_instance; };
	static LevProfiler* g_instance;

	unsigned long long m_lastTickTime;
};

LevProfiler* LevProfiler::g_instance = nullptr;
#define ProfileTimerTick KProfile::Instance()->Tick();
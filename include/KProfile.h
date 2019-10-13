#pragma once
#include <mutex>
#include <windows.h>
#include <iostream>

class KProfile
{
public:
	static KProfile* Instance()
	{
		static std::once_flag _flag;
		std::call_once(_flag, []() { g_instance = new KProfile(); });

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
	KProfile(): m_lastTickTime(0) {};
	~KProfile() { if (g_instance) delete g_instance; };
	static KProfile* g_instance;

	unsigned long long m_lastTickTime;
};

KProfile* KProfile::g_instance = nullptr;
#define ProfileTimerTick KProfile::Instance()->FrameTick();
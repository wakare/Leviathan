#include "LevTimer.h"
#include <windows.h>

namespace Leviathan
{
	LevTimer::LevTimer(float interval, TimerOutCallback callback)
		: m_interval(interval)
		, m_lastTick(GetTickCount64())
	{
		SetTimeOutCallback(callback);
	}

	void LevTimer::SetTimeOutCallback(TimerOutCallback callback)
	{
		m_callback = callback;
	}

	void LevTimer::OnTimeOut()
	{
		if (m_callback)
		{
			m_callback(*this);
		}
	}

	float LevTimer::GetLastTime() const
	{
		return m_lastTick;
	}

	float LevTimer::GetTimeInterval() const
	{
		return m_interval;
	}

	void LevTimer::UpdateCurrentTickTime()
	{
		m_lastTick = GetTickCount64();
	}
}
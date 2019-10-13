#pragma once
#include <functional>

namespace Leviathan
{
	class LevTimer;
	typedef std::function<void(const LevTimer&)> TimerOutCallback;

	class LevTimer
	{
	public: 
		LevTimer(unsigned interval, TimerOutCallback callback);
		void SetTimeOutCallback(TimerOutCallback callback);
		void OnTimeOut();
		unsigned long long GetLastTime() const;
		unsigned long long GetTimeInterval() const;
		void UpdateCurrentTickTime();

	private:
		unsigned long long m_lastTick;
		unsigned long long m_interval;
		TimerOutCallback m_callback;
	};
}
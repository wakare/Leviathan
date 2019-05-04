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
		unsigned GetLastTime() const;
		unsigned GetTimeInterval() const;
		void UpdateCurrentTickTime();

	private:
		unsigned m_lastTick;
		unsigned m_interval;
		TimerOutCallback m_callback;
	};
}
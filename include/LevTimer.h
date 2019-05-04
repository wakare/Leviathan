#pragma once
#include <functional>

namespace Leviathan
{
	class LevTimer;
	typedef std::function<void(const LevTimer&)> TimerOutCallback;

	class LevTimer
	{
	public: 
		LevTimer(float interval, TimerOutCallback callback);
		void SetTimeOutCallback(TimerOutCallback callback);
		void OnTimeOut();
		float GetLastTime() const;
		float GetTimeInterval() const;
		void UpdateCurrentTickTime();

	private:
		float m_lastTick;
		float m_interval;
		TimerOutCallback m_callback;
	};
}
#pragma once

#include <map>
#include <vector>
#include <memory>
#include <list>
#include "Event.h"
#include "EventListener.h"
#include "LSPtr.h"

namespace Leviathan
{
	class EventSystem
	{
	public:
		EventSystem() :m_currentMouseCoord(0, 0), m_bAddMouseCoordToEvent(true) {}

		virtual void DispatchEvent();
		void AddEvent(Event event);

		void AddEventListener(EventType type, EventListener* pListener)
		{
			m_eventListeners[type].push_back(pListener);
		}

		void SetCurrentMouseCoord(int x, int y)
		{
			m_currentMouseCoord.x = x; m_currentMouseCoord.y = y;
		}

		MouseCoord GetCurrentMouseCoord()
		{
			return m_currentMouseCoord;
		}

	private:
		bool m_bAddMouseCoordToEvent;
		MouseCoord m_currentMouseCoord;
		std::list<Event> m_eventQueue;
		std::map<EventType, std::vector<EventListener*>> m_eventListeners;
	};
}
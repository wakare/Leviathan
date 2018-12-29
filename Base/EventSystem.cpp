#include <iostream>
#include "EventSystem.h"
namespace Leviathan
{
	void EventSystem::DispatchEvent()
	{
		for (auto& _event : m_eventQueue)
		{
			if (m_bAddMouseCoordToEvent)
			{
				_event.m_mouseCoord = m_currentMouseCoord;
			}

			for (auto& listener : m_eventListeners[_event.m_type])
			{
				listener->Accept(_event);
			}
		}

		m_eventQueue.clear();
	}

	void EventSystem::AddEvent(Event _event)
	{
		m_eventQueue.push_back(_event);
	}
}
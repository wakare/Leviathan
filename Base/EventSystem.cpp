#include "EventSystem.h"

void EventSystem::DispatchEvent()
{
	for (auto& _event : m_eventQueue)
	{
		for (auto& listener : m_eventListeners[_event.m_type])
		{
			listener->Accept(_event);
		}
	}
}

void EventSystem::AddEvent(Event _event)
{
	m_eventQueue.push_back(_event);
}

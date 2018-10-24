#include <iostream>
#include "EventSystem.h"

void EventSystem::DispatchEvent()
{
	for (auto& _event : m_eventQueue)
	{
		std::cout << "Mouse Position" << m_currentMouseCoord.x << " " << m_currentMouseCoord.y << std::endl;
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

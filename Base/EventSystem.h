#pragma once
#include "Event.h"
#include "EventListener.h"
#include <map>
#include <vector>
#include <memory>
#include <list>

class Event;
class EventListener;



class EventSystem
{
public:
	EventSystem() :m_currentMouseCoord(0, 0), m_bAddMouseCoordToEvent(true) {}

	virtual void DispatchEvent();
	void AddEvent(Event event);
	
	void AddEventListener(Event::EventType type, std::shared_ptr<EventListener> pListener)
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
	std::map<Event::EventType, std::vector<std::shared_ptr<EventListener>>> m_eventListeners;
};
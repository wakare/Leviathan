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
	EventSystem() {}

	virtual void DispatchEvent();
	void AddEvent(Event event);

private:
	std::list<Event> m_eventQueue;
	std::map<Event::EventType, std::vector<std::shared_ptr<EventListener>>> m_eventListeners;
};
#pragma once
#include "Event.h"
#include "EventListener.h"
#include <map>
#include <vector>
#include <memory>
#include <list>

class Event;
class EventListener;

struct MouseCoord
{
	MouseCoord(int _x, int _y) :x(_x), y(_y) {}

	int x;
	int y;
};

class EventSystem
{
public:
	EventSystem() :m_currentMouseCoord(0, 0) {}

	virtual void DispatchEvent();
	void AddEvent(Event event);
	void SetCurrentMouseCoord(int x, int y) { m_currentMouseCoord.x = x; m_currentMouseCoord.y = y; }
	MouseCoord GetCurrentMouseCoord() { return m_currentMouseCoord; }

private:
	MouseCoord m_currentMouseCoord;
	std::list<Event> m_eventQueue;
	std::map<Event::EventType, std::vector<std::shared_ptr<EventListener>>> m_eventListeners;
};
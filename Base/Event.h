#pragma once

class Event
{
public:
	enum EventType
	{
		INPUT_EVENT,
		USER_EVENT,
	};

	Event(EventType type): m_type(type) {};

	EventType m_type;
};
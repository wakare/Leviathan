#pragma once

class Event
{
public:
	enum EventType
	{
		INPUT,
	};

	Event() {};

	EventType m_type;
};
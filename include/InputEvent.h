#pragma once
#include "Event.h"

class InputEvent : public Event
{
public:
	InputEvent() : Event(EventType::INPUT_EVENT) {}
private:


};
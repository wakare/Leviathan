#pragma once
#include "Event.h"

class EventListener
{
public:
	virtual void Accept(Event event) = 0;

private:
};
#pragma once
#include "Event.h"
namespace Leviathan
{
	class EventListener
	{
	public:
		virtual void Accept(Event event) = 0;
	};
}
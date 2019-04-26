#pragma once
#include "EventListener.h"

namespace Leviathan
{
	class ILevWindow : public EventListener
	{
	public:
		virtual bool Create(int width, int height, int hParent = 0) = 0;
		virtual void Run() = 0;
		virtual void Update() = 0;
		virtual void Stop() = 0;
		virtual void Accept(Event& event) = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual int GetWindowHandle() const = 0;
	};
}
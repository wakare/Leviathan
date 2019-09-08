#pragma once
#include "EventListener.h"
#include "EventSystem.h"

namespace Leviathan
{
	class ILevWindow : public EventListener, public EventSystem
	{
	public:
		ILevWindow() = default;
		virtual ~ILevWindow() = default;

		virtual bool Create(int width, int height, int hParent = 0) = 0;
		virtual bool Resize(int width, int height) = 0;
		virtual void Run() = 0;
		virtual void Update() = 0;
		virtual void SetStop() = 0;
		virtual bool HasStoped() = 0;

		virtual void Accept(Event& event) = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual int GetWindowHandle() const = 0;
	};
}
#include <memory>
#include <iostream>
#include "RenderWindow.h"
using namespace Leviathan;

int main()
{
	LPtr<EventSystem> pEventSystem = new EventSystem();
	LPtr<RenderWindow> pRenderWindow = new RenderWindow(pEventSystem);
	pEventSystem->AddEventListener(Event::EventType::INPUT_EVENT, TryCast<RenderWindow, EventListener>(pRenderWindow));

	pRenderWindow->Run();
}


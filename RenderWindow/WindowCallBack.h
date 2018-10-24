#pragma once
#include "GLFW/glfw3.h"
#include "Event.h"
#include "EventSystem.h"
#include <map>
#include <iostream>

class GLFWInputMapEventCode
{
public:
	GLFWInputMapEventCode()
	{
		dictionary[GLFW_KEY_A] = Event::InputCode::KEY_A;
		dictionary[GLFW_KEY_B] = Event::InputCode::KEY_B;
		dictionary[GLFW_KEY_C] = Event::InputCode::KEY_C;
		dictionary[GLFW_KEY_D] = Event::InputCode::KEY_D;
		dictionary[GLFW_KEY_E] = Event::InputCode::KEY_E;
		dictionary[GLFW_KEY_F] = Event::InputCode::KEY_F;
		dictionary[GLFW_KEY_G] = Event::InputCode::KEY_G;
		dictionary[GLFW_KEY_H] = Event::InputCode::KEY_H;
		dictionary[GLFW_KEY_I] = Event::InputCode::KEY_I;
		dictionary[GLFW_KEY_J] = Event::InputCode::KEY_J;
		dictionary[GLFW_KEY_K] = Event::InputCode::KEY_K;
		dictionary[GLFW_KEY_L] = Event::InputCode::KEY_L;
		dictionary[GLFW_KEY_M] = Event::InputCode::KEY_M;
		dictionary[GLFW_KEY_N] = Event::InputCode::KEY_N;
		dictionary[GLFW_KEY_O] = Event::InputCode::KEY_O;
		dictionary[GLFW_KEY_P] = Event::InputCode::KEY_P;
		dictionary[GLFW_KEY_Q] = Event::InputCode::KEY_Q;
		dictionary[GLFW_KEY_R] = Event::InputCode::KEY_R;
		dictionary[GLFW_KEY_S] = Event::InputCode::KEY_S;
		dictionary[GLFW_KEY_T] = Event::InputCode::KEY_T;
		dictionary[GLFW_KEY_W] = Event::InputCode::KEY_W;
		dictionary[GLFW_KEY_V] = Event::InputCode::KEY_V;
		dictionary[GLFW_KEY_U] = Event::InputCode::KEY_U;
		dictionary[GLFW_KEY_X] = Event::InputCode::KEY_X;
		dictionary[GLFW_KEY_Y] = Event::InputCode::KEY_Y;
		dictionary[GLFW_KEY_Z] = Event::InputCode::KEY_Z;
	}

	std::map <int, Event::InputCode> dictionary;

	Event::InputCode GetInputCode(int glfwKeyCode)
	{
		auto itInputCode = dictionary.find(glfwKeyCode);
		if (itInputCode == dictionary.end())
		{
			return Event::InputCode::KEY_NONE;
		}

		return (*itInputCode).second;
	}
};

class GLFWActionMapEvent
{
public:
	GLFWActionMapEvent()
	{
		dictionary[GLFW_PRESS] = Event::InputAction::KEYDOWN;
		dictionary[GLFW_RELEASE] = Event::InputAction::KEYUP;
	}

	Event::InputAction GetAction(int glfwAction)
	{
		auto itInputCode = dictionary.find(glfwAction);
		if (itInputCode == dictionary.end())
		{
			return Event::InputAction::NONE;
		}

		return (*itInputCode).second;
	}

	std::map <int, Event::InputAction> dictionary;
};

class WindowCallBack
{
public:
	WindowCallBack()
	{
	};


	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
	{
		Event keyEvent = Event(Event::EventType::INPUT_EVENT);
		keyEvent.m_action = m_sActionMap.GetAction(action);
		keyEvent.m_code = m_sInputMap.GetInputCode(key);

		if (keyEvent.m_action != Event::InputAction::NONE &&
			keyEvent.m_code != Event::InputCode::KEY_NONE)
		{
			m_spEventSystem->AddEvent(keyEvent);
		}
	};

	static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos) 
	{
		WindowCallBack::m_spEventSystem->SetCurrentMouseCoord(xpos, ypos);
	};

	static GLFWInputMapEventCode m_sInputMap;
	static GLFWActionMapEvent m_sActionMap;
	static std::shared_ptr<EventSystem> m_spEventSystem;
};


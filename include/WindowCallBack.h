#pragma once

#include <map>
#include <iostream>
#include "GLFW/glfw3.h"
#include "Event.h"
#include "EventSystem.h"
#include "LSPtr.h"

namespace Leviathan
{
	class GLFWInputMapEventCode
	{
	public:
		GLFWInputMapEventCode()
		{
			dictionary[GLFW_MOUSE_BUTTON_LEFT] = Event::InputCode::MOUSE_LBUTTON;
			dictionary[GLFW_MOUSE_BUTTON_RIGHT] = Event::InputCode::MOUSE_RBUTTON;
			dictionary[GLFW_MOUSE_BUTTON_MIDDLE] = Event::InputCode::MOUSE_SCROLLBUTTON;

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

			dictionary[GLFW_KEY_ESCAPE] = Event::InputCode::KEY_Escape;
		}

		std::map <int, Event::InputCode> dictionary;

		Event::InputCode GetInputCode(int glfwKeyCode)
		{
			auto itInputCode = dictionary.find(glfwKeyCode);
			if (itInputCode == dictionary.end())
			{
				return Event::InputCode::INPUT_NONE;
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
			dictionary[GLFW_REPEAT] = Event::InputAction::REPERT;
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
			auto event_system = m_window_event_system_map[window];
			if (!event_system)
			{
				return;
			}

			Event keyEvent = Event(EventType::INPUT_EVENT);
			keyEvent.m_action = m_sActionMap.GetAction(action);
			keyEvent.m_code = m_sInputMap.GetInputCode(key);

			if (keyEvent.m_action != Event::InputAction::NONE &&
				keyEvent.m_code != Event::InputCode::INPUT_NONE)
			{
				event_system->AddEvent(keyEvent);
			}
			else
			{
				LeviathanOutStream << "GLFW keyCallBack:" << key << " ,action " << action << std::endl;
			}
		};

		static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
		{
			auto event_system = m_window_event_system_map[window];
			if (!event_system)
			{
				return;
			}

			event_system->SetCurrentMouseCoord(static_cast<int>(xpos), static_cast<int>(ypos));
			Event mouseEvent = Event(EventType::INPUT_EVENT);
			mouseEvent.m_action = Event::InputAction::MOVE;
			mouseEvent.m_code = Event::InputCode::INPUT_NONE;

			event_system->AddEvent(mouseEvent);
		};

		static void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
		{
			auto event_system = m_window_event_system_map[window]; 
			if (!event_system)
			{
				return;
			}

			Event mouseEvent = Event(EventType::INPUT_EVENT);
			mouseEvent.m_action = m_sActionMap.GetAction(action);
			mouseEvent.m_code = m_sInputMap.GetInputCode(button);

			if (mouseEvent.m_action != Event::InputAction::NONE &&
				mouseEvent.m_code != Event::InputCode::INPUT_NONE)
			{
				event_system->AddEvent(mouseEvent);
			} 
		}

		static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
		{
			auto event_system = m_window_event_system_map[window];
			if (!event_system)
			{
				return;
			}

			Event scrollEvent = Event(EventType::INPUT_EVENT);
			scrollEvent.m_action = Event::InputAction::SCROLL;
			scrollEvent.m_code = Event::InputCode::INPUT_NONE;
			scrollEvent.m_context.m_mouseScrollState.x = static_cast<int>(xOffset);
			scrollEvent.m_context.m_mouseScrollState.y = static_cast<int>(yOffset);
			event_system->AddEvent(scrollEvent);
		}

		static void ResizeCallback(GLFWwindow* window, int width, int height)
		{
			auto event_system = m_window_event_system_map[window];
			if (!event_system)
			{
				return;
			}

			Event resizeEvent = Event(EventType::INPUT_EVENT);
			resizeEvent.m_action = Event::InputAction::RESIZE;
			resizeEvent.m_code = Event::InputCode::INPUT_NONE;
			resizeEvent.m_context.m_windowResizeSize.width = width;
			resizeEvent.m_context.m_windowResizeSize.height = height;
			event_system->AddEvent(resizeEvent);
		}

		static bool RegisterEventSystem(GLFWwindow* window, EventSystem* event_system)
		{
			m_window_event_system_map[window] = event_system;
			return true;
		}

		static GLFWInputMapEventCode m_sInputMap;
		static GLFWActionMapEvent m_sActionMap;
		static std::map<GLFWwindow*, EventSystem*> m_window_event_system_map;
	};
}

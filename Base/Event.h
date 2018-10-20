#pragma once
#include <windows.h>

class Event;

class Win32KeyboardMap
{
public:

	Win32KeyboardMap()
	{
		_keymap[VK_ESCAPE] = Event::InputCode::KEY_Escape;
		_keymap[VK_F1] = Event::InputCode::KEY_F1;
		_keymap[VK_F2] = Event::InputCode::KEY_F2;
		_keymap[VK_F3] = Event::InputCode::KEY_F3;
		_keymap[VK_F4] = Event::InputCode::KEY_F4;
		_keymap[VK_F5] = Event::InputCode::KEY_F5;
		_keymap[VK_F6] = Event::InputCode::KEY_F6;
		_keymap[VK_F7] = Event::InputCode::KEY_F7;
		_keymap[VK_F8] = Event::InputCode::KEY_F8;
		_keymap[VK_F9] = Event::InputCode::KEY_F9;
		_keymap[VK_F10] = Event::InputCode::KEY_F10;
		_keymap[VK_F11] = Event::InputCode::KEY_F11;
		_keymap[VK_F12] = Event::InputCode::KEY_F12;
		_keymap[0xc0] = Event::InputCode::KEY_Backquote;
		_keymap['0'] = Event::InputCode::KEY_0;
		_keymap['1'] = Event::InputCode::KEY_1;
		_keymap['2'] = Event::InputCode::KEY_2;
		_keymap['3'] = Event::InputCode::KEY_3;
		_keymap['4'] = Event::InputCode::KEY_4;
		_keymap['5'] = Event::InputCode::KEY_5;
		_keymap['6'] = Event::InputCode::KEY_6;
		_keymap['7'] = Event::InputCode::KEY_7;
		_keymap['8'] = Event::InputCode::KEY_8;
		_keymap['9'] = Event::InputCode::KEY_9;
		_keymap[0xbd] = Event::InputCode::KEY_Minus;
		_keymap[0xbb] = Event::InputCode::KEY_Equals;
		_keymap[VK_BACK] = Event::InputCode::KEY_BackSpace;
		_keymap[VK_TAB] = Event::InputCode::KEY_Tab;
		_keymap['A'] = Event::InputCode::KEY_A;
		_keymap['B'] = Event::InputCode::KEY_B;
		_keymap['C'] = Event::InputCode::KEY_C;
		_keymap['D'] = Event::InputCode::KEY_D;
		_keymap['E'] = Event::InputCode::KEY_E;
		_keymap['F'] = Event::InputCode::KEY_F;
		_keymap['G'] = Event::InputCode::KEY_G;
		_keymap['H'] = Event::InputCode::KEY_H;
		_keymap['I'] = Event::InputCode::KEY_I;
		_keymap['J'] = Event::InputCode::KEY_J;
		_keymap['K'] = Event::InputCode::KEY_K;
		_keymap['L'] = Event::InputCode::KEY_L;
		_keymap['M'] = Event::InputCode::KEY_M;
		_keymap['N'] = Event::InputCode::KEY_N;
		_keymap['O'] = Event::InputCode::KEY_O;
		_keymap['P'] = Event::InputCode::KEY_P;
		_keymap['Q'] = Event::InputCode::KEY_Q;
		_keymap['R'] = Event::InputCode::KEY_R;
		_keymap['S'] = Event::InputCode::KEY_S;
		_keymap['T'] = Event::InputCode::KEY_T;
		_keymap['U'] = Event::InputCode::KEY_U;
		_keymap['V'] = Event::InputCode::KEY_V;
		_keymap['W'] = Event::InputCode::KEY_W;
		_keymap['X'] = Event::InputCode::KEY_X;
		_keymap['Y'] = Event::InputCode::KEY_Y;
		_keymap['Z'] = Event::InputCode::KEY_Z;
		_keymap[0xdb] = Event::InputCode::KEY_Leftbracket;
		_keymap[0xdd] = Event::InputCode::KEY_Rightbracket;
		_keymap[0xdc] = Event::InputCode::KEY_Backslash;
		_keymap[VK_CAPITAL] = Event::InputCode::KEY_Caps_Lock;
		_keymap[0xba] = Event::InputCode::KEY_Semicolon;
		_keymap[0xde] = Event::InputCode::KEY_Quote;
		_keymap[VK_RETURN] = Event::InputCode::KEY_Return;
		_keymap[VK_LSHIFT] = Event::InputCode::KEY_Shift_L;
		_keymap[0xbc] = Event::InputCode::KEY_Comma;
		_keymap[0xbe] = Event::InputCode::KEY_Period;
		_keymap[0xbf] = Event::InputCode::KEY_Slash;
		_keymap[VK_RSHIFT] = Event::InputCode::KEY_Shift_R;
		_keymap[VK_LCONTROL] = Event::InputCode::KEY_Control_L;
		_keymap[VK_LWIN] = Event::InputCode::KEY_Super_L;
		_keymap[VK_SPACE] = Event::InputCode::KEY_Space;
		_keymap[VK_LMENU] = Event::InputCode::KEY_Alt_L;
		_keymap[VK_RMENU] = Event::InputCode::KEY_Alt_R;
		_keymap[VK_RWIN] = Event::InputCode::KEY_Super_R;
		_keymap[VK_APPS] = Event::InputCode::KEY_Menu;
		_keymap[VK_RCONTROL] = Event::InputCode::KEY_Control_R;
		_keymap[VK_SNAPSHOT] = Event::InputCode::KEY_Print;
		_keymap[VK_SCROLL] = Event::InputCode::KEY_Scroll_Lock;
		_keymap[VK_PAUSE] = Event::InputCode::KEY_Pause;
		_keymap[VK_HOME] = Event::InputCode::KEY_Home;
		_keymap[VK_PRIOR] = Event::InputCode::KEY_Page_Up;
		_keymap[VK_END] = Event::InputCode::KEY_End;
		_keymap[VK_NEXT] = Event::InputCode::KEY_Page_Down;
		_keymap[VK_DELETE] = Event::InputCode::KEY_Delete;
		_keymap[VK_INSERT] = Event::InputCode::KEY_Insert;
		_keymap[VK_LEFT] = Event::InputCode::KEY_Left;
		_keymap[VK_UP] = Event::InputCode::KEY_Up;
		_keymap[VK_RIGHT] = Event::InputCode::KEY_Right;
		_keymap[VK_DOWN] = Event::InputCode::KEY_Down;
		_keymap[VK_NUMLOCK] = Event::InputCode::KEY_Num_Lock;
		_keymap[VK_DIVIDE] = Event::InputCode::KEY_KP_Divide;
		_keymap[VK_MULTIPLY] = Event::InputCode::KEY_KP_Multiply;
		_keymap[VK_SUBTRACT] = Event::InputCode::KEY_KP_Subtract;
		_keymap[VK_ADD] = Event::InputCode::KEY_KP_Add;
		_keymap[VK_NUMPAD7] = Event::InputCode::KEY_KP_Home;
		_keymap[VK_NUMPAD8] = Event::InputCode::KEY_KP_Up;
		_keymap[VK_NUMPAD9] = Event::InputCode::KEY_KP_Page_Up;
		_keymap[VK_NUMPAD4] = Event::InputCode::KEY_KP_Left;
		_keymap[VK_NUMPAD5] = Event::InputCode::KEY_KP_Begin;
		_keymap[VK_NUMPAD6] = Event::InputCode::KEY_KP_Right;
		_keymap[VK_NUMPAD1] = Event::InputCode::KEY_KP_End;
		_keymap[VK_NUMPAD2] = Event::InputCode::KEY_KP_Down;
		_keymap[VK_NUMPAD3] = Event::InputCode::KEY_KP_Page_Down;
		_keymap[VK_NUMPAD0] = Event::InputCode::KEY_KP_Insert;
		_keymap[VK_DECIMAL] = Event::InputCode::KEY_KP_Delete;
		_keymap[VK_CLEAR] = Event::InputCode::KEY_Clear;
	}

	~Win32KeyboardMap() {}

	int remapKey(int key)
	{
		KeyMap::const_iterator map = _keymap.find(key);
		return map == _keymap.end() ? key : map->second;
	}

protected:

	typedef std::map<int, int> KeyMap;
	KeyMap _keymap;
};

class Event
{
public:
	enum EventType
	{
		INPUT_EVENT,
		USER_EVENT,
	};

	// Copy from OSG
	enum InputAction {
		NONE = 0,
		PUSH = 1 << 0,
		RELEASE = 1 << 1,
		DOUBLECLICK = 1 << 2,
		DRAG = 1 << 3,
		MOVE = 1 << 4,
		KEYDOWN = 1 << 5,
		KEYUP = 1 << 6,
		FRAME = 1 << 7,
		RESIZE = 1 << 8,
		SCROLL = 1 << 9,
		PEN_PRESSURE = 1 << 10,
		PEN_ORIENTATION = 1 << 11,
		PEN_PROXIMITY_ENTER = 1 << 12,
		PEN_PROXIMITY_LEAVE = 1 << 13,
		CLOSE_WINDOW = 1 << 14,
		QUIT_APPLICATION = 1 << 15,
		USER = 1 << 16
	};

	// Copy from OSG
	enum InputCode
	{
		KEY_Space = 0x20,

		KEY_0 = '0',
		KEY_1 = '1',
		KEY_2 = '2',
		KEY_3 = '3',
		KEY_4 = '4',
		KEY_5 = '5',
		KEY_6 = '6',
		KEY_7 = '7',
		KEY_8 = '8',
		KEY_9 = '9',
		KEY_A = 'a',
		KEY_B = 'b',
		KEY_C = 'c',
		KEY_D = 'd',
		KEY_E = 'e',
		KEY_F = 'f',
		KEY_G = 'g',
		KEY_H = 'h',
		KEY_I = 'i',
		KEY_J = 'j',
		KEY_K = 'k',
		KEY_L = 'l',
		KEY_M = 'm',
		KEY_N = 'n',
		KEY_O = 'o',
		KEY_P = 'p',
		KEY_Q = 'q',
		KEY_R = 'r',
		KEY_S = 's',
		KEY_T = 't',
		KEY_U = 'u',
		KEY_V = 'v',
		KEY_W = 'w',
		KEY_X = 'x',
		KEY_Y = 'y',
		KEY_Z = 'z',

		KEY_Exclaim = 0x21,
		KEY_Quotedbl = 0x22,
		KEY_Hash = 0x23,
		KEY_Dollar = 0x24,
		KEY_Ampersand = 0x26,
		KEY_Quote = 0x27,
		KEY_Leftparen = 0x28,
		KEY_Rightparen = 0x29,
		KEY_Asterisk = 0x2A,
		KEY_Plus = 0x2B,
		KEY_Comma = 0x2C,
		KEY_Minus = 0x2D,
		KEY_Period = 0x2E,
		KEY_Slash = 0x2F,
		KEY_Colon = 0x3A,
		KEY_Semicolon = 0x3B,
		KEY_Less = 0x3C,
		KEY_Equals = 0x3D,
		KEY_Greater = 0x3E,
		KEY_Question = 0x3F,
		KEY_At = 0x40,
		KEY_Leftbracket = 0x5B,
		KEY_Backslash = 0x5C,
		KEY_Rightbracket = 0x5D,
		KEY_Caret = 0x5E,
		KEY_Underscore = 0x5F,
		KEY_Backquote = 0x60,

		KEY_BackSpace = 0xFF08,        /* back space, back char */
		KEY_Tab = 0xFF09,
		KEY_Linefeed = 0xFF0A,        /* Linefeed, LF */
		KEY_Clear = 0xFF0B,
		KEY_Return = 0xFF0D,        /* Return, enter */
		KEY_Pause = 0xFF13,        /* Pause, hold */
		KEY_Scroll_Lock = 0xFF14,
		KEY_Sys_Req = 0xFF15,
		KEY_Escape = 0xFF1B,
		KEY_Delete = 0xFFFF,        /* Delete, rubout */


		/* Cursor control & motion */

		KEY_Home = 0xFF50,
		KEY_Left = 0xFF51,        /* Move left, left arrow */
		KEY_Up = 0xFF52,        /* Move up, up arrow */
		KEY_Right = 0xFF53,        /* Move right, right arrow */
		KEY_Down = 0xFF54,        /* Move down, down arrow */
		KEY_Prior = 0xFF55,        /* Prior, previous */
		KEY_Page_Up = 0xFF55,
		KEY_Next = 0xFF56,        /* Next */
		KEY_Page_Down = 0xFF56,
		KEY_End = 0xFF57,        /* EOL */
		KEY_Begin = 0xFF58,        /* BOL */


		/* Misc Functions */

		KEY_Select = 0xFF60,        /* Select, mark */
		KEY_Print = 0xFF61,
		KEY_Execute = 0xFF62,        /* Execute, run, do */
		KEY_Insert = 0xFF63,        /* Insert, insert here */
		KEY_Undo = 0xFF65,        /* Undo, oops */
		KEY_Redo = 0xFF66,        /* redo, again */
		KEY_Menu = 0xFF67,        /* On Windows, this is VK_APPS, the context-menu key */
		KEY_Find = 0xFF68,        /* Find, search */
		KEY_Cancel = 0xFF69,        /* Cancel, stop, abort, exit */
		KEY_Help = 0xFF6A,        /* Help */
		KEY_Break = 0xFF6B,
		KEY_Mode_switch = 0xFF7E,        /* Character set switch */
		KEY_Script_switch = 0xFF7E,        /* Alias for mode_switch */
		KEY_Num_Lock = 0xFF7F,

		/* Keypad Functions, keypad numbers cleverly chosen to map to ascii */

		KEY_KP_Space = 0xFF80,        /* space */
		KEY_KP_Tab = 0xFF89,
		KEY_KP_Enter = 0xFF8D,        /* enter */
		KEY_KP_F1 = 0xFF91,        /* PF1, KP_A, ... */
		KEY_KP_F2 = 0xFF92,
		KEY_KP_F3 = 0xFF93,
		KEY_KP_F4 = 0xFF94,
		KEY_KP_Home = 0xFF95,
		KEY_KP_Left = 0xFF96,
		KEY_KP_Up = 0xFF97,
		KEY_KP_Right = 0xFF98,
		KEY_KP_Down = 0xFF99,
		KEY_KP_Prior = 0xFF9A,
		KEY_KP_Page_Up = 0xFF9A,
		KEY_KP_Next = 0xFF9B,
		KEY_KP_Page_Down = 0xFF9B,
		KEY_KP_End = 0xFF9C,
		KEY_KP_Begin = 0xFF9D,
		KEY_KP_Insert = 0xFF9E,
		KEY_KP_Delete = 0xFF9F,
		KEY_KP_Equal = 0xFFBD,        /* equals */
		KEY_KP_Multiply = 0xFFAA,
		KEY_KP_Add = 0xFFAB,
		KEY_KP_Separator = 0xFFAC,       /* separator, often comma */
		KEY_KP_Subtract = 0xFFAD,
		KEY_KP_Decimal = 0xFFAE,
		KEY_KP_Divide = 0xFFAF,

		KEY_KP_0 = 0xFFB0,
		KEY_KP_1 = 0xFFB1,
		KEY_KP_2 = 0xFFB2,
		KEY_KP_3 = 0xFFB3,
		KEY_KP_4 = 0xFFB4,
		KEY_KP_5 = 0xFFB5,
		KEY_KP_6 = 0xFFB6,
		KEY_KP_7 = 0xFFB7,
		KEY_KP_8 = 0xFFB8,
		KEY_KP_9 = 0xFFB9,

		/*
		* Auxiliary Functions; note the duplicate definitions for left and right
		* function keys;  Sun keyboards and a few other manufactures have such
		* function key groups on the left and/or right sides of the keyboard.
		* We've not found a keyboard with more than 35 function keys total.
		*/

		KEY_F1 = 0xFFBE,
		KEY_F2 = 0xFFBF,
		KEY_F3 = 0xFFC0,
		KEY_F4 = 0xFFC1,
		KEY_F5 = 0xFFC2,
		KEY_F6 = 0xFFC3,
		KEY_F7 = 0xFFC4,
		KEY_F8 = 0xFFC5,
		KEY_F9 = 0xFFC6,
		KEY_F10 = 0xFFC7,
		KEY_F11 = 0xFFC8,
		KEY_F12 = 0xFFC9,
		KEY_F13 = 0xFFCA,
		KEY_F14 = 0xFFCB,
		KEY_F15 = 0xFFCC,
		KEY_F16 = 0xFFCD,
		KEY_F17 = 0xFFCE,
		KEY_F18 = 0xFFCF,
		KEY_F19 = 0xFFD0,
		KEY_F20 = 0xFFD1,
		KEY_F21 = 0xFFD2,
		KEY_F22 = 0xFFD3,
		KEY_F23 = 0xFFD4,
		KEY_F24 = 0xFFD5,
		KEY_F25 = 0xFFD6,
		KEY_F26 = 0xFFD7,
		KEY_F27 = 0xFFD8,
		KEY_F28 = 0xFFD9,
		KEY_F29 = 0xFFDA,
		KEY_F30 = 0xFFDB,
		KEY_F31 = 0xFFDC,
		KEY_F32 = 0xFFDD,
		KEY_F33 = 0xFFDE,
		KEY_F34 = 0xFFDF,
		KEY_F35 = 0xFFE0,

		/* Modifiers */

		KEY_Shift_L = 0xFFE1,        /* Left shift */
		KEY_Shift_R = 0xFFE2,        /* Right shift */
		KEY_Control_L = 0xFFE3,        /* Left control */
		KEY_Control_R = 0xFFE4,        /* Right control */
		KEY_Caps_Lock = 0xFFE5,        /* Caps lock */
		KEY_Shift_Lock = 0xFFE6,        /* Shift lock */

		KEY_Meta_L = 0xFFE7,        /* Left meta */
		KEY_Meta_R = 0xFFE8,        /* Right meta */
		KEY_Alt_L = 0xFFE9,        /* Left alt */
		KEY_Alt_R = 0xFFEA,        /* Right alt */
		KEY_Super_L = 0xFFEB,        /* Left super */
		KEY_Super_R = 0xFFEC,        /* Right super */
		KEY_Hyper_L = 0xFFED,        /* Left hyper */
		KEY_Hyper_R = 0xFFEE         /* Right hyper */
	};

	Event(EventType type): m_type(type) {};

	EventType m_type;
	InputAction action;
	InputCode code;
};
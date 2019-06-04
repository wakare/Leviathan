#pragma once

#include "LPtr.h"

namespace Leviathan
{
	enum LevWindowType
	{
		ELWT_OPENGL
	};

	class ILevWindow;

	class LevWindowFactory
	{
	public:
		LevWindowFactory();
		static bool Create(LevWindowType type, LPtr<ILevWindow>& out);
	};
}
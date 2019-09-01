#pragma once

#include "LPtr.h"
#include "LevCoreExport.h"

namespace Leviathan
{
	enum LevWindowType
	{
		ELWT_OPENGL
	};

	class ILevWindow;

	class LEV_CORE_API LevWindowFactory
	{
	public:
		LevWindowFactory();
		static bool Create(LevWindowType type, LPtr<ILevWindow>& out);
	};
}
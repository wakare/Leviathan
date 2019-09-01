#pragma once

#include "LevCoreExport.h"

namespace Leviathan
{
	class LEV_CORE_API GeometryCalculator
	{
	public:
		static void CalNormal(float* vertex0, float* vertex1, float* vertex2, float* outNormal);
	};
}
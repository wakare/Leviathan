#pragma once

namespace Leviathan
{
	class GeometryCalculator
	{
	public:
		static void CalNormal(float* vertex0, float* vertex1, float* vertex2, float* outNormal);
	};
}
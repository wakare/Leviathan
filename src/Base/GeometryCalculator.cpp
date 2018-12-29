#include "GeometryCalculator.h"
#include "VectorOperation.h"

void Leviathan::GeometryCalculator::CalNormal(float* vertex0, float* vertex1, float* vertex2, float* outNormal)
{
	float edge0[3] =
	{
		vertex0[0] - vertex1[0],
		vertex0[1] - vertex1[1],
		vertex0[2] - vertex1[2],
	};

	float edge1[3] =
	{
		vertex1[0] - vertex2[0],
		vertex1[1] - vertex2[1],
		vertex1[2] - vertex2[2],
	};

	Vec3Cross(edge0, edge1, outNormal, true);
}

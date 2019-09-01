#pragma once
#include <cstring>
#include <cmath>
#include "LevCoreExport.h"
#include "GlobalDef.h"

class LEV_CORE_API AABB
{
public:
	AABB(const float* _min, const float* _max)
		: inited(false)
	{
		SetData(_min, _max);
	}

	AABB() 
		: inited(false)
	{
	};

	void SetData(const float* _min, const float* _max)
	{
		std::memcpy(min, _min, sizeof(float) * 3);
		std::memcpy(max, _max, sizeof(float) * 3);
		center[0] = 0.5f * (min[0] + max[0]);
		center[1] = 0.5f * (min[1] + max[1]);
		center[2] = 0.5f * (min[2] + max[2]);

		inited = true;
	}

	float Radius() const
	{
		LEV_ASSERT(inited);
		return 1.5f * (center[0] - min[0]);
	}

	const float* Center() const
	{
		LEV_ASSERT(inited);
		return center;
	}

	const float* Min() const
	{
		LEV_ASSERT(inited);
		return min;
	}

	const float* Max() const
	{
		LEV_ASSERT(inited);
		return max;
	}
 
	void Merge(const AABB& rhs)
	{
		if (!inited)
		{
			SetData(rhs.Min(), rhs.Max());
			return;
		}

		auto _rMin = rhs.Min();
		min[0] = fmin(min[0], _rMin[0]);
		min[1] = fmin(min[1], _rMin[1]);
		min[2] = fmin(min[2], _rMin[2]);

		auto _rMax = rhs.Max();
		max[0] = fmin(max[0], _rMax[0]);
		max[1] = fmin(max[1], _rMax[1]);
		max[2] = fmin(max[2], _rMax[2]);

		center[0] = 0.5f * (min[0] + max[0]);
		center[1] = 0.5f * (min[1] + max[1]);
		center[2] = 0.5f * (min[2] + max[2]);
	}

private:
	bool inited;
	float min[3];
	float max[3];
	float center[3];
};

inline bool AABBInside(const AABB& refAABB, const AABB& testAABB)
{
	return
		refAABB.Min()[0] <= testAABB.Min()[0] && refAABB.Max()[0] >= testAABB.Max()[0] &&
		refAABB.Min()[1] <= testAABB.Min()[1] && refAABB.Max()[1] >= testAABB.Max()[1] &&
		refAABB.Min()[2] <= testAABB.Min()[2] && refAABB.Max()[2] >= testAABB.Max()[2];
}

inline bool AABBIntersect(const AABB& refAABB, const AABB& testAABB)
{
	bool xIntersect = !(refAABB.Min()[0] > testAABB.Max()[0] || refAABB.Max()[0] < testAABB.Min()[0]);
	bool yIntersect = !(refAABB.Min()[1] > testAABB.Max()[1] || refAABB.Max()[1] < testAABB.Min()[1]);
	bool zIntersect = !(refAABB.Min()[2] > testAABB.Max()[2] || refAABB.Max()[2] < testAABB.Min()[2]);

	return xIntersect && yIntersect && zIntersect;
}
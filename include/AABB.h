#pragma once
#include <cstring>

class AABB
{
public:
	AABB(float* _min, float* _max)
	{
		SetData(_min, _max);
	}

	AABB() 
	{
	};

	void SetData(float* _min, float* _max)
	{
		std::memcpy(min, _min, sizeof(float) * 3);
		std::memcpy(max, _max, sizeof(float) * 3);
		center[0] = 0.5f * (min[0] + max[0]);
		center[1] = 0.5f * (min[1] + max[1]);
		center[2] = 0.5f * (min[2] + max[2]);
	}

	float Radius() const
	{
		return 1.5f * (center[0] - min[0]);
	}

	float min[3];
	float max[3];
	float center[3];
};

inline bool AABBInside(const AABB& refAABB, const AABB& testAABB)
{
	return
		refAABB.min[0] <= testAABB.min[0] && refAABB.max[0] >= testAABB.max[0] &&
		refAABB.min[1] <= testAABB.min[1] && refAABB.max[1] >= testAABB.max[1] &&
		refAABB.min[2] <= testAABB.min[2] && refAABB.max[2] >= testAABB.max[2];
}

inline bool AABBIntersect(const AABB& refAABB, const AABB& testAABB)
{
	bool xIntersect = !(refAABB.min[0] > testAABB.max[0] || refAABB.max[0] < testAABB.min[0]);
	bool yIntersect = !(refAABB.min[1] > testAABB.max[1] || refAABB.max[1] < testAABB.min[1]);
	bool zIntersect = !(refAABB.min[2] > testAABB.max[2] || refAABB.max[2] < testAABB.min[2]);

	return xIntersect && yIntersect && zIntersect;
}
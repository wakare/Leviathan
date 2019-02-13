#pragma once

namespace Leviathan
{
	namespace SpaceAccStruct
	{
		template <typename scalar = float>
		struct AABB
		{
			AABB(scalar* _min, scalar* _max)
			{
				memcpy(min, _min, sizeof(scalar) * 3);
				memcpy(max, _max, sizeof(scalar) * 3);
				center[0] = 0.5f * (min[0] + max[0]);
				center[1] = 0.5f * (min[1] + max[1]);
				center[2] = 0.5f * (min[2] + max[2]);
			}

			AABB() {};

			virtual bool RayIntersect(float* rayPos, float* rayDir, float& distance)
			{
				if (AABBInside(*this, AABB<float>(rayPos, rayPos)))
				{
					distance = 0.0f;
					return true;
				}

				static auto swap = [](float& a, float& b)
				{
					float temp = a;
					a = b;
					b = temp;
				};

				distance = -1.0f;
				float tmin = (min[0] - rayPos[0]) / rayDir[0];
				float tmax = (max[0] - rayPos[0]) / rayDir[0];

				if (tmin > tmax) swap(tmin, tmax);

				float tymin = (min[1] - rayPos[1]) / rayDir[1];
				float tymax = (max[1] - rayPos[1]) / rayDir[1];

				if (tymin > tymax) swap(tymin, tymax);

				if ((tmin > tymax) || (tymin > tmax))
					return false;

				if (tymin > tmin)
					tmin = tymin;

				if (tymax < tmax)
					tmax = tymax;

				float tzmin = (min[2] - rayPos[2]) / rayDir[2];
				float tzmax = (max[2] - rayPos[2]) / rayDir[2];

				if (tzmin > tzmax) swap(tzmin, tzmax);

				if ((tmin > tzmax) || (tzmin > tmax))
					return false;

				if (tzmin > tmin)
					tmin = tzmin;

				if (tzmax < tmax)
					tmax = tzmax;

				distance = tmin;
				return true;
			}

			scalar min[3];
			scalar max[3];
			scalar center[3];
		};

		template<typename scalar = float>
		inline bool AABBInside(const AABB<scalar>& refAABB, const AABB<scalar>& testAABB)
		{
			return
				refAABB.min[0] <= testAABB.min[0] && refAABB.max[0] >= testAABB.max[0] &&
				refAABB.min[1] <= testAABB.min[1] && refAABB.max[1] >= testAABB.max[1] &&
				refAABB.min[2] <= testAABB.min[2] && refAABB.max[2] >= testAABB.max[2];
		}

		template<typename scalar = float>
		inline bool AABBIntersect(const AABB<scalar>& refAABB, const AABB<scalar>& testAABB)
		{
			bool xIntersect = !(refAABB.min[0] >= testAABB.max[0] || refAABB.max[0] <= testAABB.min[0]);
			bool yIntersect = !(refAABB.min[1] >= testAABB.max[1] || refAABB.max[1] <= testAABB.min[1]);
			bool zIntersect = !(refAABB.min[2] >= testAABB.max[2] || refAABB.max[2] <= testAABB.min[2]);

			return xIntersect && yIntersect && zIntersect;
		}

		template <typename scalar = float>
		class ISpaceAccStruct
		{
		public:
			virtual void AddNode(const AABB<scalar>& node) = 0;
			virtual const AABB<scalar>& Pick(float* rayPos, float* rayDir) = 0;
		};
	}
}
#pragma once
#include "GlobalDef.h"
#include <memory>

namespace Leviathan
{
	class AABB
	{
		union AABBCoord
		{
			struct
			{
				float minX;
				float minY;
				float minZ;
				float maxX;
				float maxY;
				float maxZ;
			};

			float coord[6];
		};

	public:
		AABB(float* data = nullptr) : m_bSetFlag(false), m_fRadius(-1.0f)
		{
			if (data)
			{
				SetAABBCoord(data);
			}
		};

		void SetAABBCoord(float* data)
		{
			memcpy(&m_coord, data, sizeof(AABBCoord));
			m_fRadius = 0.5f * (fmax(fmax(m_coord.maxX - m_coord.minX, m_coord.maxY - m_coord.minY), m_coord.maxZ - m_coord.minZ));
			
			m_bSetFlag = true;
		}

		bool HasSet() const
		{
			return m_bSetFlag;
		}

		AABB Merge(const AABB& rhs) const
		{
			float mergedAABB[6] = 
			{
				m_coord.minX < rhs.m_coord.minX ? m_coord.minX : rhs.m_coord.minX,
				m_coord.minY < rhs.m_coord.minY ? m_coord.minY : rhs.m_coord.minY,
				m_coord.minZ < rhs.m_coord.minZ ? m_coord.minZ : rhs.m_coord.minZ,
				m_coord.maxX > rhs.m_coord.maxX ? m_coord.maxX : rhs.m_coord.maxX,
				m_coord.maxY > rhs.m_coord.maxY ? m_coord.maxY : rhs.m_coord.maxY,
				m_coord.maxZ > rhs.m_coord.maxZ ? m_coord.maxZ : rhs.m_coord.maxZ,
			};

			return mergedAABB;
		}

		const AABBCoord& GetAABBCoord()
		{
			if (!m_bSetFlag)
			{
				LeviathanOutStream << "[ERROR] Try to access invalid AABB coord." << std::endl;
				throw "Exception";
			}

			return m_coord;
		}

		bool GetAABBCenter(float* outCenter) const
		{
			if (!m_bSetFlag)
			{
				LeviathanOutStream << "[ERROR] Try to access invalid AABB coord." << std::endl;
				return false;
			}

			outCenter[0] = 0.5f * (m_coord.minX + m_coord.maxX);
			outCenter[1] = 0.5f * (m_coord.minY + m_coord.maxY);
			outCenter[2] = 0.5f * (m_coord.minZ + m_coord.maxZ);

			return true;
		}

		float GetAABBRadius() const
		{
			if (!m_bSetFlag)
			{
				LeviathanOutStream << "[ERROR] Try to access invalid AABB coord." << std::endl;
				return -1.0f;
			}

			return m_fRadius;
		}

	private:
		bool m_bSetFlag;
		AABBCoord m_coord;
		float m_fRadius;
	};
}
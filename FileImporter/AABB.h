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
		AABB(float* data = nullptr) : m_bSetFlag(false)
		{
			if (data)
			{
				SetAABBCoord(data);
			}
		};

		void SetAABBCoord(float* data)
		{
			m_bSetFlag = true;
			memcpy(&m_coord, data, sizeof(AABBCoord));
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

			return 0.5f * (fmax(fmax(m_coord.maxX - m_coord.minX, m_coord.maxY - m_coord.minY), m_coord.maxZ - m_coord.minZ));
		}

	private:
		bool m_bSetFlag;
		AABBCoord m_coord;
	};
}
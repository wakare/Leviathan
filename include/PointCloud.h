#pragma once
#include <memory>
#include "DynamicArray.h"

namespace Leviathan
{
	template<typename scalar>
	struct PointCloud
	{
		PointCloud(unsigned pointCount, scalar* coordData, scalar* normalData = nullptr) :
			m_bWithNormal(normalData != nullptr)
		{
			// Alloc
			size_t size = pointCount * 3 * sizeof(scalar);
			m_pCoord = new DynamicArray<scalar>(size);
			memcpy((*m_pCoord).m_pData, coordData, size);
			m_pointCount = pointCount;

			if (m_bWithNormal)
			{
				m_pNormal = new DynamicArray<scalar>(size);
				memcpy((*m_pNormal).m_pData, normalData, size);
			}
		}

		bool HasNormal() const
		{
			return m_bWithNormal;
		}

		bool GetCenterAndRadius(scalar* outCenter, scalar& outRadius)
		{
			scalar* pCoord = m_pCoord->m_pData;
			scalar min[3] = { pCoord[0], pCoord[1], pCoord[2]};
			scalar max[3] = { pCoord[0], pCoord[1], pCoord[2]};

			for (unsigned i = 0; i < m_pointCount; i++)
			{
				scalar* pCoord = m_pCoord->m_pData + i * 3;

				if (pCoord[0] < min[0]) min[0] = pCoord[0];
				if (pCoord[1] < min[1]) min[1] = pCoord[1];
				if (pCoord[2] < min[2]) min[2] = pCoord[2];

				if (pCoord[0] > max[0]) max[0] = pCoord[0];
				if (pCoord[1] > max[1]) max[1] = pCoord[1];
				if (pCoord[2] > max[2]) max[2] = pCoord[2];
			}

			outCenter[0] = 0.5f * (min[0] + max[0]);
			outCenter[1] = 0.5f * (min[1] + max[1]);
			outCenter[2] = 0.5f * (min[2] + max[2]);

			scalar length[3] = { (max[0] - min[0]) , (max[1] - min[1]),(max[2] - min[2]) };
			outRadius = 0.5f * (length[0] > length[1] ? (length[0] > length[2] ? length[0] : length[2]) : (length[1] > length[2] ? length[1] : length[2]));

			return true;
		}

		LPtr<DynamicArray<scalar>> m_pCoord;
		LPtr<DynamicArray<scalar>> m_pNormal;
		size_t m_pointCount;
		bool m_bWithNormal;
	};

	#define PointCloudf PointCloud<float>
}
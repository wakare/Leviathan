#pragma once
#include <memory>
#include "DynamicArray.h"

namespace Leviathan
{
	template<typename scalar>
	struct PointCloud
	{
		PointCloud(scalar* coordData, unsigned pointCount)
		{
			// Alloc
			size_t size = pointCount * 3 * sizeof(scalar);
			m_pCoord = new DynamicArray<scalar>(size);

			memcpy((*m_pCoord).m_pData, coordData, size);
			m_pointCount = pointCount;
		}

		LPtr<DynamicArray<scalar>> m_pCoord;
		size_t m_pointCount;
	};

	#define PointCloudf PointCloud<float>
}
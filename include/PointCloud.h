#pragma once

#include <memory>
#include "DynamicArray.h"
#include "LPtr.h"

namespace Leviathan
{
	template<typename scalar>
	struct PointCloud
	{
		PointCloud(unsigned pointCount, scalar* coordData, scalar* normalData = nullptr);
		bool HasNormal() const;
		bool GetCenterAndRadius(scalar* outCenter, scalar& outRadius);

		LPtr<DynamicArray<scalar>> m_pCoord;
		LPtr<DynamicArray<scalar>> m_pNormal;
		size_t m_pointCount;
		bool m_bWithNormal;
	};

	#define PointCloudf PointCloud<float>
}

#include "PointCloud.hpp"
#pragma once

#include <memory>
#include "DynamicArray.h"
#include "LPtr.h"
#include "IResource.h"

namespace Leviathan
{
	template<typename scalar>
	struct PointCloud : public IResource
	{
		PointCloud(unsigned pointCount, scalar* coordData, scalar* normalData = nullptr);
		bool HasNormal() const;
		bool GetCenterAndRadius(scalar* outCenter, scalar& outRadius);
		EResourceType Type() const;
		
		bool m_bWithNormal;
		size_t m_pointCount;

		LPtr<DynamicArray<scalar>> m_pCoord;
		LPtr<DynamicArray<scalar>> m_pNormal;
	};
	
	#define PointCloudf PointCloud<float>
}

#include "PointCloud.hpp"
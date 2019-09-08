#pragma once

#include <memory>
#include "DynamicArray.h"
#include "LSPtr.h"
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

		LSPtr<DynamicArray<scalar>> m_pCoord;
		LSPtr<DynamicArray<scalar>> m_pNormal;
	};
	
	typedef PointCloud<float> PointCloudf;
}

#include "PointCloud.hpp"
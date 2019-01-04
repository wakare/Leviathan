#pragma once
#include "LPtr.h"

namespace Leviathan
{
	class GLObject;
	class AABB;

	class SceneHelper
	{
	public:
		static LPtr<GLObject> _convertAABBtoGLObject(const AABB& aabb);
		static LPtr<GLObject> _getPointGLObject(float* pCoordData, unsigned uVertexCount, float *pColorData = nullptr);

	private:
		SceneHelper();
	};
}
#pragma once
#include "AABB.h"
#include "LPtr.h"
#include "GLObject.h"
#include "IModelStruct.h"

namespace Leviathan
{
	namespace SceneBase 
	{
		LPtr<GLObject> _convertModelFileToGLObject(LPtr<IModelStruct> modelFile);
		LPtr<GLObject> _convertAABBtoGLObject(const AABB& aabb);
		LPtr<GLObject> _getPointGLObject(float* pCoordData, unsigned uVertexCount, float *pColorData = nullptr);
	};
}
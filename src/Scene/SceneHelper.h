#pragma once
#include "LPtr.h"

namespace Leviathan
{
	class GLObject;
	class AABB;
	class GLShaderProgram;

	class SceneHelper
	{
	public:
		static LPtr<GLObject> _convertAABBtoGLObject(const AABB& aabb);
		static LPtr<GLObject> _getPointGLObject(float* pCoordData, unsigned uVertexCount, float *pColorData = nullptr);
		static bool _initShaderSource(const char* pczVertexShaderPath, const char* pczFragmentShaderPath, LPtr<GLShaderProgram>& outResult);
		static std::string _getShaderSource(const char* pczShaderSourcePath);

	private:
		SceneHelper();
	};
}
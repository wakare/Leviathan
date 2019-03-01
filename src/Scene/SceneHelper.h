#pragma once

#include "LPtr.h"
class AABB;

namespace Leviathan
{
	class GLObject;
	class GLShaderProgram;
	class SceneNode;

	template<typename T>
	class Node;

	class SceneHelper
	{
	public:
		static LPtr<GLObject> ConvertAABBtoGLObject(const AABB& aabb);
		static LPtr<GLObject> GetPointGLObject(float* pCoordData, unsigned uVertexCount, float *pColorData = nullptr);
		static std::string GetShaderSource(const char* pczShaderSourcePath);

		static bool InitShaderSource(const char* pczVertexShaderPath, const char* pczFragmentShaderPath, LPtr<GLShaderProgram>& outResult);
		static bool LoadModel(const char* pModelFilePath, LPtr<Node<SceneNode>>& out);
	private:
		SceneHelper();
	};
}
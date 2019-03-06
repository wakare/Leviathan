#include <fstream>
#include <sstream>
#include "AABB.h"
#include "SceneHelper.h"
#include "SceneNode.h"
#include "DrawableNode.h"
#include "TriDGLObject.h"
#include "DynamicArray.h"
#include "GLShaderProgram.h"

namespace Leviathan
{
	Leviathan::LPtr<Leviathan::GLObject> SceneHelper::ConvertAABBtoGLObject(const AABB& aabb)
	{
		float fRadius = aabb.Radius();
		if (fRadius < 0.0f)
		{
			LeviathanOutStream << "[ERROR] AABB radius less than zero." << std::endl;
			return nullptr;
		}

		constexpr int nVertexFloatCount = 10;
		float fNormalSubValue = sqrtf(1.0f / 3.0f);

		float vertices[8 * nVertexFloatCount] =
		{
			-fRadius, -fRadius, -fRadius,  1.0f, 0.0f, 0.0f, 1.0f, -fNormalSubValue, -fNormalSubValue, -fNormalSubValue,// 0.0f, 0.0f,
			fRadius, -fRadius, -fRadius,  0.0f, 1.0f, 0.0f, 1.0f,  fNormalSubValue, -fNormalSubValue, -fNormalSubValue,// 1.0f, 0.0f,
			fRadius,  fRadius, -fRadius,  0.0f, 0.0f, 1.0f, 1.0f,  fNormalSubValue,  fNormalSubValue, -fNormalSubValue,// 1.0f, 1.0f,
			-fRadius,  fRadius, -fRadius,  0.0f, 1.0f, 0.0f, 1.0f, -fNormalSubValue,  fNormalSubValue, -fNormalSubValue,// 0.0f, 1.0f,
			-fRadius, -fRadius,  fRadius,  1.0f, 0.0f, 0.0f, 1.0f, -fNormalSubValue, -fNormalSubValue,  fNormalSubValue,// 1.0f, 1.0f,
			fRadius, -fRadius,  fRadius,  0.0f, 1.0f, 0.0f, 1.0f,  fNormalSubValue, -fNormalSubValue,  fNormalSubValue,// 0.0f, 1.0f,
			fRadius,  fRadius,  fRadius,  0.0f, 0.0f, 1.0f, 1.0f,  fNormalSubValue,  fNormalSubValue,  fNormalSubValue,// 0.0f, 0.0f,
			-fRadius,  fRadius,  fRadius,  0.0f, 1.0f, 0.0f, 1.0f, -fNormalSubValue,  fNormalSubValue,  fNormalSubValue,// 1.0f, 0.0f,
		};

		// Move to center
		const float* center = aabb.center;

		for (unsigned i = 0; i < 8; i++)
		{
			vertices[nVertexFloatCount * i] += center[0];
			vertices[nVertexFloatCount * i + 1] += center[1];
			vertices[nVertexFloatCount * i + 2] += center[2];
		}

		constexpr unsigned uCubeTriangleCount = 36;
		unsigned vertexIndices[uCubeTriangleCount] =
		{
			0, 1, 2, 0, 2, 3,
			1, 5, 6, 1, 6, 2,
			3, 2, 6, 3, 6, 7,
			0, 7, 4, 0, 3, 7,
			0, 5, 1, 0, 4, 5,
			4, 6, 5, 4, 7, 6
		};

		auto vertexTypeMask = TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA | TriDGLObject::VERTEX_ATTRIBUTE_NXYZ;
		auto result = new TriDGLObject(GL_TRIANGLES, vertices, 8, vertexTypeMask, nullptr, nullptr, vertexIndices, uCubeTriangleCount);
		return result;
	}

	Leviathan::LPtr<Leviathan::GLObject> SceneHelper::GetPointGLObject(float* pCoordData, unsigned uVertexCount, float *pColorData /*= nullptr*/)
	{
		static float defaultColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		const int nVertexSize = 7;
		DynamicArray<float> pArray(uVertexCount * nVertexSize * sizeof(float));

		for (unsigned i = 0; i < uVertexCount; i++)
		{
			memcpy(pArray.m_pData + nVertexSize * i, pCoordData + 3 * i, sizeof(float) * 3);

			if (pColorData)		memcpy(pArray.m_pData + nVertexSize * i + 3, pColorData + 4 * i, sizeof(float) * 4); 
			else				memcpy(pArray.m_pData + nVertexSize * i + 3, defaultColor, sizeof(float) * 4); 
		}

		return new TriDGLObject(GL_POINTS, pArray.m_pData, uVertexCount, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA);
	}

	bool SceneHelper::InitShaderSource(const char* pczVertexShaderPath, const char* pczFragmentShaderPath, LPtr<GLShaderProgram>& outResult)
	{
		auto strVertexShader = GetShaderSource(pczVertexShaderPath);
		auto strFragmentShader = GetShaderSource(pczFragmentShaderPath);

		const char* pczVertexShaderSource = strVertexShader.c_str();
		const char* pczFragmentShaderSource = strFragmentShader.c_str();

		outResult = new GLShaderProgram(&pczVertexShaderSource, &pczFragmentShaderSource, nullptr);
		return true;
	}

	bool SceneHelper::LoadModel(const char* pModelFilePath, LPtr<Node<SceneNode>>& out)
	{
		auto pSceneNode = LPtr<SceneNode>(new SceneNode());
		EXIT_IF_FALSE(pSceneNode->LoadModelFile(pModelFilePath));
		LPtr<DrawableNode<SceneNode>> pModelNode = new DrawableNode<SceneNode>(pSceneNode->GetMeshVec(), pSceneNode);

		auto pGLObjectVec = pModelNode->GetGLObject();
		for (auto pGLObject : pGLObjectVec)
		{
			Eigen::Matrix4f modelMatrix = pModelNode->GetNodeData()->GetWorldTransform();
			pGLObject->SetModelMatrix(modelMatrix);
		}

		out = TryCast<DrawableNode<SceneNode>, Node<SceneNode>>(pModelNode);
		return true;
	}

	std::string SceneHelper::GetShaderSource(const char* pczShaderSourcePath)
	{
		std::ifstream shaderSourceFileStream(pczShaderSourcePath, std::ios::in);
		if (!shaderSourceFileStream.is_open())
		{
			throw "std::string Scene::_getShaderSource(const char* pczShaderSourcePath) --> Invalid ShaderSource paths.";
			return std::string();
		}

		std::stringstream strStream;
		strStream << shaderSourceFileStream.rdbuf();
		return strStream.str();
	}
}
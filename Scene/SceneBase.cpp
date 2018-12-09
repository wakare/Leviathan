#include "SceneBase.h"
#include "DynamicArray.h"
#include "GeometryCalculator.h"
#include "TriDGLObject.h"


Leviathan::LPtr<Leviathan::GLObject> Leviathan::SceneBase::_convertModelFileToGLObject(LPtr<IModelStruct> modelFile)
{
	const unsigned uVertexFloatCount = 10;

	DynamicArray<float> glData(modelFile->GetTriangleCount() * 3 * uVertexFloatCount * sizeof(float));

	static float defaultColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	bool bDefaultColor = false;

	auto color = modelFile->GetVertexColorArray();
	if (!color)
	{
		bDefaultColor = true;
	}

	for (unsigned i = 0; i < modelFile->GetTriangleCount(); i++)
	{
		unsigned* vertexIndex = modelFile->GetTriangleIndexArray() + 3 * i;
		float* vertices[3];

		for (unsigned j = 0; j < 3; j++)
		{
			float* vertexCoord = modelFile->GetVertex3DCoordArray() + 3 * vertexIndex[j];
			vertices[j] = vertexCoord;
			memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j, vertexCoord, sizeof(float) * 3);

			if (bDefaultColor)
			{
				memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j + 3, defaultColor, sizeof(float) * 4);
			}
			else
			{
				memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j + 3, color + 4 * i, sizeof(float) * 4);
			}
		}

		float fNormal[3];
		GeometryCalculator::CalNormal(vertices[0], vertices[1], vertices[2], fNormal);

		for (unsigned j = 0; j < 3; j++)
		{
			memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j + 7, fNormal, sizeof(float) * 3);
		}
	}

	return new TriDGLObject(GL_TRIANGLES, glData.m_pData, modelFile->GetTriangleCount() * 3, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA | TriDGLObject::VERTEX_ATTRIBUTE_NXYZ);
}

Leviathan::LPtr<Leviathan::GLObject> Leviathan::SceneBase::_convertAABBtoGLObject(const AABB& aabb)
{
	float fRadius = aabb.GetAABBRadius();
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
	float center[3];
	aabb.GetAABBCenter(center);

	for (unsigned i = 0; i < 8; i++)
	{
		vertices[nVertexFloatCount * i] += center[0];
		vertices[nVertexFloatCount * i + 1] += center[1];
		vertices[nVertexFloatCount * i + 2] += center[2];
	}

	constexpr unsigned uCubeTriangleCount = 36;
	unsigned vertexIndices[uCubeTriangleCount] =
	{
		0, 1, 2,
		0, 2, 3,
		1, 5, 6,
		1, 6, 2,
		3, 2, 6,
		3, 6, 7,
		0, 7, 4,
		0, 3, 7,
		0, 5, 1,
		0, 4, 5,
		4, 6, 5,
		4, 7, 6
	};

	//auto result = new TriDGLObject(GL_TRIANGLES, cube, 36, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA | TriDGLObject::VERTEX_ATTRIBUTE_NXYZ | TriDGLObject::VERTEX_ATTRIBUTE_TEX);
	auto result = new TriDGLObject(GL_TRIANGLES, vertices, 8, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA | TriDGLObject::VERTEX_ATTRIBUTE_NXYZ /*| TriDGLObject::VERTEX_ATTRIBUTE_TEX*/, nullptr, nullptr, vertexIndices, uCubeTriangleCount);
	return result;
}

Leviathan::LPtr<Leviathan::GLObject> Leviathan::SceneBase::_getPointGLObject(float* pCoordData, unsigned uVertexCount, float *pColorData /*= nullptr*/)
{
	static float defaultColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const int nVertexSize = 7;
	DynamicArray<float> pArray(uVertexCount * nVertexSize * sizeof(float));

	for (unsigned i = 0; i < uVertexCount; i++)
	{
		memcpy(pArray.m_pData + nVertexSize * i, pCoordData + 3 * i, sizeof(float) * 3);

		if (pColorData)
		{
			memcpy(pArray.m_pData + nVertexSize * i + 3, pColorData + 4 * i, sizeof(float) * 4);
		}
		else
		{
			memcpy(pArray.m_pData + nVertexSize * i + 3, defaultColor, sizeof(float) * 4);
		}
	}

	return new TriDGLObject(GL_POINTS, pArray.m_pData, uVertexCount, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA);
}

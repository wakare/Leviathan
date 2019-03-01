#include "CMesh.h"
#include "GlobalDef.h"

namespace Leviathan
{
	CMesh::CMesh(size_t uVertexCount, size_t uPrimitiveCount, EPrimitiveType type) :
		m_vertexNumber(uVertexCount),
		m_primitiveNumber(uPrimitiveCount),
		m_vertexCoords(nullptr),
		m_primitiveIndex(nullptr),
		m_vertexColorData(nullptr),
		m_vertexTexData(nullptr),
		m_pMaterial(nullptr),
		m_primitiveType(type)
	{

	}

	CMesh::~CMesh()
	{
	}

	IMesh::EPrimitiveType CMesh::GetPrimitiveType() const
	{
		return m_primitiveType;
	}

	unsigned CMesh::GetVertexCount()
	{
		return m_vertexNumber;
	}

	unsigned CMesh::GetPrimitiveCount()
	{
		return m_primitiveNumber;
	}

	float* CMesh::GetVertex3DCoordArray()
	{
		if (!m_vertexCoords) return nullptr;
		return m_vertexCoords->m_pData;
	}

	float * CMesh::GetVertexNormalArray()
	{
		if (!m_vertexNormal) return nullptr;
		return m_vertexNormal->m_pData;
	}

	float* CMesh::GetVertexColorArray()
	{
		if (!m_vertexColorData) return nullptr;
		return m_vertexColorData->m_pData;
	}

	float* CMesh::GetVertexTexArray()
	{
		if (!m_vertexTexData) return nullptr;
		return m_vertexTexData->m_pData;
	}

	unsigned* CMesh::GetPrimitiveIndexArray()
	{
		if (!m_primitiveIndex) return nullptr;
		return m_primitiveIndex->m_pData;
	}

	void CMesh::SetVertexCoordData(float* vertexCoordData)
	{
		m_vertexCoords = new DynamicArray<float>(sizeof(float) * 3 * m_vertexNumber);
		memcpy(m_vertexCoords->m_pData, vertexCoordData, sizeof(float) * 3 * m_vertexNumber);
	}

	void CMesh::SetVertexNormalData(float * vertexNormalData)
	{
		m_vertexNormal = new DynamicArray<float>(sizeof(float) * 3 * m_vertexNumber);
		memcpy(m_vertexNormal->m_pData, vertexNormalData, sizeof(float) * 3 * m_vertexNumber);
	}

	void CMesh::SetPrimitiveIndexData(unsigned* primitiveIndexData)
	{
		m_primitiveIndex = new DynamicArray<unsigned>(sizeof(float) * 3 * m_primitiveNumber);
		memcpy(m_primitiveIndex->m_pData, primitiveIndexData, sizeof(unsigned) * 3 * m_primitiveNumber);
	}

	void CMesh::SetVertexTex2DData(float* vertexTexData)
	{
		m_vertexTexData = new DynamicArray<float>(sizeof(float) * 2 * m_vertexNumber);
		memcpy(m_vertexTexData->m_pData, vertexTexData, sizeof(float) * 2 * m_vertexNumber);
	}

	void CMesh::SetVertexColorData(float* vertexColorData)
	{
		m_vertexColorData = new DynamicArray<float>(sizeof(float) * 3 * m_vertexNumber);
		memcpy(m_vertexColorData->m_pData, vertexColorData, sizeof(float) * 3 * m_vertexNumber);
	}

	void CMesh::SetMaterial(LPtr<Material> material)
	{
		m_pMaterial = material;
	}

	Leviathan::LPtr<Material> CMesh::GetMaterial()
	{
		return m_pMaterial;
	}

	const AABB& CMesh::GetAABB()
{
		if (!m_bAABBInited)
		{
			if (!_setAABB())
			{
				throw "Exception";
			}
		}

		return m_AABB;
	}

	bool CMesh::_setAABB()
	{
		float AABBData[6];
		bool bInited = false;

		// Traverse vertex coord
		for (unsigned i = 0; i < m_vertexNumber; i++)
		{
			float* currentVertexCoord = m_vertexCoords->m_pData + 3 * i;

			if (!bInited)
			{
				AABBData[0] = currentVertexCoord[0];
				AABBData[1] = currentVertexCoord[1];
				AABBData[2] = currentVertexCoord[2];
				AABBData[3] = currentVertexCoord[0];
				AABBData[4] = currentVertexCoord[1];
				AABBData[5] = currentVertexCoord[2];

				bInited = true;
				continue;
			}

			for (unsigned j = 0; j < 3; j++)
			{
				if (currentVertexCoord[j] < AABBData[j])
				{
					AABBData[j] = currentVertexCoord[j];
				}

				if (currentVertexCoord[j] > AABBData[3 + j])
				{
					AABBData[3 + j] = currentVertexCoord[j];
				}
			}
		}

		if (!bInited)
		{
			LeviathanOutStream << "[FATAL] AABB init failed." << std::endl;
			return false;
		}

		m_AABB.SetData(AABBData, AABBData + 3);
		return true;
	}

}
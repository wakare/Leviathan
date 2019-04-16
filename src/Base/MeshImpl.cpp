#include "MeshImpl.h"
#include "GlobalDef.h"

namespace Leviathan
{
	MeshImpl::MeshImpl(size_t uVertexCount, size_t uPrimitiveCount, EPrimitiveType type) :
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

	MeshImpl::~MeshImpl()
	= default;

	IMesh::EPrimitiveType MeshImpl::GetPrimitiveType() const
	{
		return m_primitiveType;
	}

	void MeshImpl::SetPrimitiveType(EPrimitiveType type)
	{
		m_primitiveType = type;
	}

	unsigned MeshImpl::GetVertexCount()
	{
		return m_vertexNumber;
	}

	unsigned MeshImpl::GetPrimitiveCount()
	{
		return m_primitiveNumber;
	}

	void MeshImpl::SetPrimitiveCount(unsigned count)
	{
		m_primitiveNumber = count;
	}

	float* MeshImpl::GetVertex3DCoordArray()
	{
		if (!m_vertexCoords) return nullptr;
		return m_vertexCoords->m_pData;
	}

	float * MeshImpl::GetVertexNormalArray()
	{
		if (!m_vertexNormal) return nullptr;
		return m_vertexNormal->m_pData;
	}

	float* MeshImpl::GetVertexColorArray()
	{
		if (!m_vertexColorData) return nullptr;
		return m_vertexColorData->m_pData;
	}

	float* MeshImpl::GetVertexTexArray()
	{
		if (!m_vertexTexData) return nullptr;
		return m_vertexTexData->m_pData;
	}

	unsigned* MeshImpl::GetPrimitiveIndexArray()
	{
		if (!m_primitiveIndex) return nullptr;
		return m_primitiveIndex->m_pData;
	}

	void MeshImpl::SetVertexCoordData(float* vertexCoordData)
	{
		m_vertexCoords = new DynamicArray<float>(sizeof(float) * 3 * m_vertexNumber);
		memcpy(m_vertexCoords->m_pData, vertexCoordData, sizeof(float) * 3 * m_vertexNumber);
	}

	void MeshImpl::SetVertexNormalData(float * vertexNormalData)
	{
		m_vertexNormal = new DynamicArray<float>(sizeof(float) * 3 * m_vertexNumber);
		memcpy(m_vertexNormal->m_pData, vertexNormalData, sizeof(float) * 3 * m_vertexNumber);
	}

	void MeshImpl::SetPrimitiveIndexData(unsigned* primitiveIndexData)
	{
		m_primitiveIndex = new DynamicArray<unsigned>(sizeof(float) * 3 * m_primitiveNumber);
		memcpy(m_primitiveIndex->m_pData, primitiveIndexData, sizeof(unsigned) * 3 * m_primitiveNumber);
	}

	void MeshImpl::SetVertexTex2DData(float* vertexTexData)
	{
		m_vertexTexData = new DynamicArray<float>(sizeof(float) * 2 * m_vertexNumber);
		memcpy(m_vertexTexData->m_pData, vertexTexData, sizeof(float) * 2 * m_vertexNumber);
	}

	void MeshImpl::SetVertexColorData(float* vertexColorData)
	{
		m_vertexColorData = new DynamicArray<float>(sizeof(float) * 3 * m_vertexNumber);
		memcpy(m_vertexColorData->m_pData, vertexColorData, sizeof(float) * 3 * m_vertexNumber);
	}

	void MeshImpl::SetMaterial(LPtr<Material> material)
	{
		m_pMaterial = material;
	}

	Leviathan::LPtr<Material> MeshImpl::GetMaterial()
	{
		return m_pMaterial;
	}

	const AABB& MeshImpl::GetAABB()
{
		if (!m_bAABBInited)
		{
			if (!_setAABB())
			{
				throw "Exception";
			}

			m_bAABBInited = true;
		}

		return m_AABB;
	}

	Leviathan::EResourceType MeshImpl::Type() const
	{
		return ERT_MESH;
	}

	bool MeshImpl::_setAABB()
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
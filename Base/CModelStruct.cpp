#include "CModelStruct.h"
#include "GlobalDef.h"

namespace Leviathan
{
	CModelStruct::CModelStruct() : 
		m_vertexNumber(0),
		m_triangleNumber(0),
		m_vertexCoords(nullptr),
		m_triangleIndex(nullptr),
		m_vertexColorData(nullptr),
		m_vertexTexData(nullptr),
		m_pMaterial(nullptr)
	{

	}

	CModelStruct::~CModelStruct()
	{
		if (m_vertexCoords)
		{
			free(m_vertexCoords);
			m_vertexCoords = nullptr;
		}

		if (m_triangleIndex)
		{
			free(m_triangleIndex);
			m_triangleIndex = nullptr;
		}

		if (m_vertexColorData)
		{
			free(m_vertexColorData);
			m_vertexColorData = nullptr;
		}

		if (m_vertexTexData)
		{
			free(m_vertexTexData);
			m_vertexTexData = nullptr;
		}
	}

	unsigned CModelStruct::GetVertexCount()
	{
		return m_vertexNumber;
	}

	float* CModelStruct::GetVertex3DCoordArray()
	{
		return m_vertexCoords;
	}

	float* CModelStruct::GetVertexColorArray()
	{
		return m_vertexColorData;
	}

	float* CModelStruct::GetVertexTexArray()
	{
		return m_vertexTexData;
	}

	unsigned CModelStruct::GetTriangleCount()
	{
		return m_triangleNumber;
	}

	unsigned* CModelStruct::GetTriangleIndexArray()
	{
		return m_triangleIndex;
	}

	void CModelStruct::SetVertexCoordData(unsigned uVertexCount, float* vertexCoordData)
	{
		m_vertexNumber = uVertexCount;
		m_vertexCoords = (float*)malloc(sizeof(float) * 3 * m_vertexNumber);

		memcpy(m_vertexCoords, vertexCoordData, sizeof(float) * 3 * m_vertexNumber);
	}

	void CModelStruct::SetTriangleIndexData(unsigned uTriangleCount, unsigned* triangleIndexData)
	{
		m_triangleNumber = uTriangleCount;
		m_triangleIndex = (unsigned*)malloc(sizeof(unsigned) * 3 * m_triangleNumber);

		memcpy(m_triangleIndex, triangleIndexData, sizeof(unsigned) * 3 * m_triangleNumber);
	}

	void CModelStruct::SetVertexTex2DData(unsigned uVertexCount, float* vertexTexData)
	{
		m_vertexNumber = uVertexCount;
		m_vertexTexData = (float*)malloc(sizeof(float) * 2 * m_vertexNumber);

		memcpy(m_vertexTexData, vertexTexData, sizeof(float) * 2 * m_vertexNumber);
	}

	void CModelStruct::SetVertexColorData(unsigned uVertexCount, float* vertexColorData)
	{
		m_vertexNumber = uVertexCount;
		m_vertexColorData = (float*)malloc(sizeof(float) * 3 * m_vertexNumber);

		memcpy(m_vertexColorData, vertexColorData, sizeof(float) * 3 * m_vertexNumber);
	}

	void CModelStruct::SetMaterial(LPtr<Material> material)
	{
		m_pMaterial = material;
	}

	Leviathan::LPtr<Material> CModelStruct::GetMaterial()
	{
		return m_pMaterial;
	}

	const Leviathan::AABB& CModelStruct::GetAABB()
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

	bool CModelStruct::_setAABB()
{
		float AABBData[6];
		bool bInited = false;

		// Traverse vertex coord
		for (unsigned i = 0; i < m_vertexNumber; i++)
		{
			float* currentVertexCoord = m_vertexCoords + 3 * i;

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

		m_AABB.SetAABBCoord(AABBData);
		return true;
	}

}
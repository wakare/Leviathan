#include "CModelStruct.h"
#include "GlobalDef.h"

namespace Leviathan
{
	CModelStruct::CModelStruct()
	{

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
		return nullptr;
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
		if (m_vertexNumber > 0)
		{
			LeviathanOutStream << "[WARN] Set multiple vertex coord data" <<std::endl;
		}

		m_vertexNumber = uVertexCount;
		memcpy(m_vertexCoords, vertexCoordData, sizeof(float) * 3 * m_vertexNumber);
	}

	void CModelStruct::SetTriangleIndexData(unsigned uTriangleCount, unsigned* triangleIndexData)
	{
		if (m_triangleNumber > 0)
		{
			LeviathanOutStream << "[WARN] Set multiple triangle index data" << std::endl;
		}

		m_triangleNumber = uTriangleCount;
		memcpy(m_triangleIndex, triangleIndexData, sizeof(unsigned) * 3 * m_triangleNumber);
	}

}
#pragma once

#include "IMesh.h"
#include "DynamicArray.h"

class AABB;

namespace Leviathan
{
	class CMesh : public IMesh
	{
	public:
		CMesh(size_t uVertexCount, size_t uPrimitiveCount, EPrimitiveType type = IMesh::EPT_TRIANGLES);
		~CMesh();

		EPrimitiveType GetPrimitiveType() const;

		unsigned GetVertexCount();
		unsigned GetPrimitiveCount();
		unsigned* GetPrimitiveIndexArray();
		float* GetVertex3DCoordArray();
		float* GetVertexNormalArray();
		float* GetVertexColorArray();
		float* GetVertexTexArray();

		void SetVertexCoordData(float* vertexCoordData);
		void SetVertexNormalData(float* vertexNormalData);
		void SetPrimitiveIndexData(unsigned* triangleIndexData);
		void SetVertexTex2DData(float* vertexTexData);
		void SetVertexColorData(float* vertexColorData);
		void SetMaterial(LPtr<Material> material);

		LPtr<Material> GetMaterial();
		const AABB& GetAABB();

	private:
		bool _setAABB();

		EPrimitiveType m_primitiveType;

		LPtr<DynamicArray<unsigned>> m_primitiveIndex;
		unsigned	m_primitiveNumber;

		LPtr<DynamicArray<float>> m_vertexCoords;
		LPtr<DynamicArray<float>> m_vertexNormal;
		LPtr<DynamicArray<float>> m_vertexColorData;
		LPtr<DynamicArray<float>> m_vertexTexData;

		unsigned	m_vertexNumber;
		LPtr<Material> m_pMaterial;

		bool		m_bAABBInited;
		AABB		m_AABB;
	};
}
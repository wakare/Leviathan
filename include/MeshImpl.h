#pragma once

#include "IMesh.h"
#include "DynamicArray.h"

class AABB;

/*
	TODO:
		Split mesh impl into trangleMesh and pointCloudMesh
*/

namespace Leviathan
{
	class MeshImpl : public IMesh
	{
	public:
		MeshImpl(size_t uVertexCount, size_t uPrimitiveCount, EPrimitiveType type = IMesh::EPT_TRIANGLES);
		~MeshImpl();

		EPrimitiveType GetPrimitiveType() const;
		void SetPrimitiveType(EPrimitiveType type);

		unsigned GetPrimitiveCount();
		void SetPrimitiveCount(unsigned count);
		 
		unsigned GetVertexCount();
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
		void SetMaterial(LSPtr<Material> material);

		LSPtr<Material> GetMaterial();
		const AABB& GetAABB();

		EResourceType Type() const;

	private:
		bool _setAABB();

		EPrimitiveType m_primitiveType;

		LSPtr<DynamicArray<unsigned>> m_primitiveIndex;
		unsigned	m_primitiveNumber;

		LSPtr<DynamicArray<float>> m_vertexCoords;
		LSPtr<DynamicArray<float>> m_vertexNormal;
		LSPtr<DynamicArray<float>> m_vertexColorData;
		LSPtr<DynamicArray<float>> m_vertexTexData;

		unsigned	m_vertexNumber;
		LSPtr<Material> m_pMaterial;

		bool		m_bAABBInited;
		AABB		m_AABB;
	};
}
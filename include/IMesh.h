#pragma once

#include "AABB.h"
#include "Material.h"
#include "LSPtr.h"
#include "IResource.h"

namespace Leviathan
{
	class IMesh : public IResource
	{
	public:
		enum EPrimitiveType 
		{
			EPT_POINTS = 1,
			EPT_LINES = 2,
			EPT_TRIANGLES = 3,
		};

		virtual EPrimitiveType GetPrimitiveType() const = 0;
		virtual void SetPrimitiveType(EPrimitiveType) = 0;

		virtual unsigned	GetPrimitiveCount() = 0;
		virtual void		SetPrimitiveCount(unsigned) = 0;

		virtual unsigned	GetVertexCount() = 0;
		virtual unsigned*	GetPrimitiveIndexArray() = 0;
		virtual float*		GetVertex3DCoordArray() = 0;
		virtual float*		GetVertexNormalArray() = 0;
		virtual float*		GetVertexColorArray() = 0;
		virtual float*		GetVertexTexArray() = 0;

		virtual void SetVertexCoordData(float* vertexCoordData) = 0;
		virtual void SetVertexNormalData(float* vertexNormalData) = 0;
		virtual void SetPrimitiveIndexData(unsigned* triangleIndexData) = 0;
		virtual void SetVertexTex2DData(float* vertexTexData) = 0;
		virtual void SetVertexColorData(float* vertexColorData) = 0;
		virtual void SetMaterial(LSPtr<Material> material) = 0;

		virtual LSPtr<Material> GetMaterial() = 0;
		virtual const AABB& GetAABB() = 0;

		virtual EResourceType Type() const = 0;

	protected:
		IMesh() {};
	};
}
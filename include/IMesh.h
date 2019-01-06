#pragma once

#include "AABB.h"
#include "Material.h"
#include "LPtr.h"

namespace Leviathan
{
	class IMesh
	{
	public:
		enum EPrimitiveType 
		{
			EPT_POINTS = 1,
			EPT_LINES = 2,
			EPT_TRIANGLES = 3,
		};

		virtual EPrimitiveType GetPrimitiveType() const = 0;

		virtual unsigned	GetVertexCount() = 0;
		virtual unsigned	GetPrimitiveCount() = 0;

		virtual unsigned*	GetPrimitiveIndexArray() = 0;
		virtual float*		GetVertex3DCoordArray() = 0;
		virtual float*		GetVertexNormalArray() = 0;
		virtual float*		GetVertexColorArray() = 0;
		virtual float*		GetVertexTexArray() = 0;

		virtual LPtr<Material> GetMaterial() = 0;
		virtual const AABB& GetAABB() = 0;

	protected:
		IMesh() {};
	};
}
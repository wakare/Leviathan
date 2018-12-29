#pragma once
#include "AABB.h"
#include "Material.h"
#include "LPtr.h"

namespace Leviathan
{
	class IModelStruct
	{
	public:
		virtual unsigned	GetVertexCount() = 0;
		virtual unsigned	GetTriangleCount() = 0;

		virtual unsigned*	GetTriangleIndexArray() = 0;
		virtual float*		GetVertex3DCoordArray() = 0;
		virtual float*		GetVertexColorArray() = 0;
		virtual float*		GetVertexTexArray() = 0;

		virtual LPtr<Material> GetMaterial() = 0;
		virtual const AABB& GetAABB() = 0;

	protected:
		IModelStruct() {};
	};
}
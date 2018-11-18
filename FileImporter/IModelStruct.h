#pragma once
#include "AABB.h"

namespace Leviathan
{
	class IModelFile
	{
	public:
		virtual unsigned	GetVertexCount() = 0;
		virtual unsigned	GetTriangleCount() = 0;

		virtual unsigned*	GetTriangleIndexArray() = 0;
		virtual float*		GetVertex3DCoordArray() = 0;
		virtual float*		GetVertexColorArray() = 0;
		virtual const AABB& GetAABB() = 0;
	protected:
		IModelFile() {};
	};
}
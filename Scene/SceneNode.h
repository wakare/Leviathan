#pragma once
#include "BaseMath.h"

namespace Leviathan
{
	class SceneNode
	{
	public:
		SceneNode();
		void SetModelMatrix(Matrix4f&);
		const Matrix4f& GetModelMatrix() const;

	private:
		Matrix4f m_modelMatrix;
	};
}
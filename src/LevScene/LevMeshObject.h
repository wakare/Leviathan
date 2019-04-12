#pragma once

#include <vector>
#include "LevSceneObjectDescription.h"
#include "IMesh.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevMeshObject : public LevSceneObjectDescription
		{
		public:
			LevMeshObject();

			bool LoadMeshFile(const char* meshFile);
			const std::vector<LPtr<IMesh>>& GetMesh() const;
			const AABB& GetAABB() const;

		private:
			std::vector<LPtr<IMesh>> m_mesh;
			LPtr<AABB> m_pMeshAABB;
		};
	}
}
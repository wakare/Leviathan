#pragma once

#include <vector>
#include "LevSceneObjectDescription.h"
#include "IMesh.h"
#include "LevRAttrObjectColor.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevMeshObject : public LevSceneObjectDescription
		{
		public:
			LevMeshObject();

			bool LoadMeshFile(const char* meshFile);

			bool SetMesh(const std::vector<LPtr<IMesh>>& meshes);
			bool SetMesh(LPtr<IMesh> pMesh);

			const std::vector<LPtr<IMesh>>& GetMesh() const;
			const AABB& GetAABB() const;

			bool SetColorData(LevObjectColorType type, const LevObjectColorData& data);

		private:
			void _updateAABB();

			std::vector<LPtr<IMesh>> m_mesh;
			LPtr<AABB> m_pMeshAABB;
		};
	}
}
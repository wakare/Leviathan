#pragma once

#include <vector>
#include "LevSceneObjectDescription.h"
#include "IMesh.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevMeshObject : public LevSceneObjectDescription
		{
		public:
			LevMeshObject();

			bool LoadMeshFile(const char* meshFile);

			bool SetMesh(const std::vector<LSPtr<IMesh>>& meshes);
			bool SetMesh(LSPtr<IMesh> pMesh);

			const std::vector<LSPtr<IMesh>>& GetMesh() const;
			const AABB& GetAABB() const;

		private:
			void _updateAABB();

			std::vector<LSPtr<IMesh>> m_mesh;
			LSPtr<AABB> m_pMeshAABB;
		};
	}
}
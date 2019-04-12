#include "LevMeshObject.h"
#include "GlobalDef.h"
#include "CFileImportFactory.h"

namespace Leviathan
{
	namespace Scene
	{
		LevMeshObject::LevMeshObject()
			: LevSceneObjectDescription(ELSOD_MESH)
			, m_pMeshAABB(nullptr)
		{
			
		}

		bool LevMeshObject::LoadMeshFile(const char* meshFile)
		{
			// Can only load mesh once
			EXIT_IF_FALSE(m_mesh.size() == 0);

			m_mesh = CFileImportFactory::GetFileImportFactory()->LoadFile(meshFile);
			EXIT_IF_FALSE(m_mesh.size() > 0);

			// Init AABB
			m_pMeshAABB.Reset(new AABB);
			for (const auto& mesh : m_mesh)
			{
				m_pMeshAABB->Merge(mesh->GetAABB());
			}

			return true;
		}

		const std::vector<LPtr<IMesh>>& LevMeshObject::GetMesh() const
		{
			LEV_ASSERT(m_mesh.size() > 0);
			return m_mesh;
		}
		const AABB & LevMeshObject::GetAABB() const
		{
			return *m_pMeshAABB;
		}
	}
}


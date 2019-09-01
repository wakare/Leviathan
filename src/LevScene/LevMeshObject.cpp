#include "LevMeshObject.h"
#include "GlobalDef.h"
#include "FileImportFactory.h"

namespace Leviathan
{
	namespace Scene
	{
		LevMeshObject::LevMeshObject()
			: LevSceneObjectDescription(ELSOD_MESH_TRIANGLE)
			, m_pMeshAABB(nullptr)
		{
			
		}

		bool LevMeshObject::LoadMeshFile(const char* meshFile)
		{
			// Can only load mesh once
			EXIT_IF_FALSE(m_mesh.size() == 0);

			m_mesh = FileImportFactory::GetFileImportFactory()->LoadFile(meshFile);
			EXIT_IF_FALSE(m_mesh.size() > 0);
			_updateAABB();

			return true;
		}

		bool LevMeshObject::SetMesh(const std::vector<LPtr<IMesh>>& meshes)
		{
			m_mesh = meshes;
			_updateAABB();
			
			return true;
		}

		bool LevMeshObject::SetMesh(LPtr<IMesh> pMesh)
		{
			m_mesh.clear();
			m_mesh.push_back(pMesh);
			_updateAABB();

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

		void LevMeshObject::_updateAABB()
		{
			// Init AABB
			m_pMeshAABB.Reset(new AABB);
			for (const auto& mesh : m_mesh)
			{
				m_pMeshAABB->Merge(mesh->GetAABB());
			}
		}
	}
}


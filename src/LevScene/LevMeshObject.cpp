#include "LevMeshObject.h"
#include "GlobalDef.h"
#include "IFileImportFactory.h"

namespace Leviathan
{
	namespace Scene
	{
		LevMeshObject::LevMeshObject():
			LevSceneObjectDescription(ELSOD_MESH)
		{
			
		}

		bool LevMeshObject::LoadMeshFile(const char* meshFile)
		{
			m_mesh = IFileImportFactory::GetFileImportFactory()->LoadFile(meshFile);
			return m_mesh.size() > 0;
		}

		const std::vector<LPtr<IMesh>>& LevMeshObject::GetMesh() const
		{
			LEV_ASSERT(m_mesh.size() > 0);
			return m_mesh;
		}
	}
}


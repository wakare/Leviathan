#include "LevMeshObject.h"
#include "GlobalDef.h"
#include "CFileImportFactory.h"
#include "LevRAttrObjectColor.h"

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

			return false;
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

		bool LevMeshObject::SetColorData(LevObjectColorType type, const LevObjectColorData& colorData)
		{
			switch (type)
			{
			case Scene::ELOCT_PURE_COLOR:
			{
				for (auto& mesh : GetMesh())
				{
					float* meshColor = new float[mesh->GetVertexCount() * 3 * sizeof(float)];
					for (unsigned i = 0; i < mesh->GetVertexCount(); i++)
					{
						float *data = meshColor + 3 * i;
						memcpy(data, colorData.pure_color, 3 * sizeof(float));
					}

					mesh->SetVertexColorData(meshColor);
					delete[] meshColor;
				}
				break;
			}

			case Scene::ELOCT_COLOR_ARRAY:
			{
				auto* meshColor = colorData.color_array;
				for (auto& mesh : GetMesh())
				{
					mesh->SetVertexColorData(meshColor);
					unsigned byteSize = mesh->GetVertexCount() * 3 * sizeof(float);
					meshColor += byteSize;
				}
				break;
			}

			default:
				return false;
			}

			return true;
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


#include "LevToolInterface.h"
#include "PresenterScheduler.h"
#include "ViewScheduler.h"
#include "FileImportFactory.h"
#include "LevSceneObject.h"
#include "LevMeshObject.h"
#include "GlobalDef.h"
#include "MeshImpl.h"
#include "LevSceneNode.h"

namespace Leviathan
{
	inline PresenterScheduler& _scheduler()
	{
		return PresenterScheduler::Instance();
	}

	bool LevToolInterface::LoadPointCloudFile(const char * file, LPtr<PointCloudf>& out)
	{
		auto loaded_mesh = FileImportFactory::GetFileImportFactory()->LoadFile(file);

		unsigned point_count = 0;
		for (auto& mesh : loaded_mesh)
		{
			point_count += mesh->GetVertexCount();
		}

		auto* coord_data = new float[3 * point_count];
		auto* normal_data = new float[3 * point_count];

		auto* current_coord_data = coord_data;
		auto* current_normal_data = normal_data;

		for (auto& mesh : loaded_mesh)
		{
			auto mesh_vertex_count = mesh->GetVertexCount();

			LEV_ASSERT(mesh->GetVertex3DCoordArray());
			LEV_ASSERT(mesh->GetVertexNormalArray());

			memcpy(current_coord_data, mesh->GetVertex3DCoordArray(), 3 * mesh_vertex_count * sizeof(float));
			memcpy(current_normal_data, mesh->GetVertexNormalArray(), 3 * mesh_vertex_count * sizeof(float));

			current_coord_data += 3 * mesh_vertex_count;
			current_normal_data += 3 * mesh_vertex_count;
		}

		out.Reset(new PointCloudf(point_count, coord_data, normal_data));
		delete[] coord_data;
		delete[] normal_data;

		return true;
	}

	bool LevToolInterface::LoadMesh(const char* file, std::vector<LPtr<IMesh>>& out)
	{
		out = FileImportFactory::GetFileImportFactory()->LoadFile(file);
		return true;
	}

	bool LevToolInterface::SetPointCloudData(LPtr<PointCloudf> point_cloud, LPtr<Scene::LevSceneNode> out_node)
	{
		EXIT_IF_FALSE(out_node);

		LPtr<MeshImpl> mesh = new MeshImpl(point_cloud->m_pointCount, 0, IMesh::EPT_POINTS);
		mesh->SetVertexCoordData(point_cloud->m_pCoord->m_pData);
		mesh->SetVertexNormalData(point_cloud->m_pNormal->m_pData);
		std::vector<LPtr<IMesh>> meshes; meshes.push_back(TryCast<MeshImpl, IMesh>(mesh));

		EXIT_IF_FALSE(SetMeshData(meshes, out_node));

		return true;
	}

	bool LevToolInterface::SetMeshData(const std::vector<LPtr<IMesh>>& point_cloud, LPtr<Scene::LevSceneNode> out_node)
	{
		auto& obj_desc = out_node->GetNodeData()->GetObjectDesc();
		Scene::LevMeshObject* mesh_object = dynamic_cast<Scene::LevMeshObject*>(&obj_desc);
		EXIT_IF_FALSE(mesh_object);

		mesh_object->SetMesh(point_cloud);
		return true;
	}

}
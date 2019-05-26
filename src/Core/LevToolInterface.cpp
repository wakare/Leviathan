#include "LevToolInterface.h"
#include "PresenterScheduler.h"
#include "ViewScheduler.h"
#include "FileImportFactory.h"

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

}
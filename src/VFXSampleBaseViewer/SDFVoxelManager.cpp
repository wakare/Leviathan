#include "SDFVoxelManager.h"
#include "GlobalDef.h"

namespace Leviathan
{
	namespace Viewer
	{
		SDFVoxelManager::SDFVoxelManager(unsigned dimension, const float* min, const float* max)
			: m_dimension(dimension)
			, m_square_dimension(m_dimension * m_dimension)
		{
			memcpy(m_min, min, sizeof(m_min));
			memcpy(m_max, max, sizeof(m_max));

			m_grid_length[0] = m_max[0] - m_min[0];
			m_grid_length[1] = m_max[1] - m_min[1];
			m_grid_length[2] = m_max[2] - m_min[2];

			m_grid_unit_length[0] = (m_max[0] - m_min[0]) / static_cast<float>(m_dimension);
			m_grid_unit_length[1] = (m_max[1] - m_min[1]) / static_cast<float>(m_dimension);
			m_grid_unit_length[2] = (m_max[2] - m_min[2]) / static_cast<float>(m_dimension);

			m_inverse_grid_unit_length[0] = 1.0f / m_grid_unit_length[0];
			m_inverse_grid_unit_length[1] = 1.0f / m_grid_unit_length[1];
			m_inverse_grid_unit_length[2] = 1.0f / m_grid_unit_length[2];

			m_grids.resize(m_dimension * m_square_dimension);

			m_grid_merged_func = [this](SDFVoxel& be_merged, const SDFVoxel& merged_grid)
			{
				be_merged.weight = merged_grid.weight;
				return true;
			};
		}

		void SDFVoxelManager::UpdateSDFVoxel(const float* world_coord, const SDFVoxel& voxel)
		{
			LEV_ASSERT(Inside(world_coord));

			unsigned index = GetIndexByCoord(world_coord);
			LEV_ASSERT(index < m_grids.size());

			auto& grid = m_grids[index];
			bool merged = m_grid_merged_func(grid, voxel);
			LEV_ASSERT(merged);
		}

		void SDFVoxelManager::UpdateSDFVoxelByFunc(SDFVoxelUpdateFunc update_func)
		{
			for (size_t i = 0 ;i < m_grids.size(); i++)
			{
				auto& grid = m_grids[i];
				float world_coord[3];
				GetCoordByIndex(i, world_coord);

				//LogLine("world_coord" << world_coord[0] << " " << world_coord[1] << " " << world_coord[2] << " ");

				update_func(world_coord, grid);
			}
		}

		const std::vector<SDFVoxel>& SDFVoxelManager::GetAllGrids() const
		{
			return m_grids;
		}

		const float* SDFVoxelManager::GetSize() const
		{
			return m_grid_length;
		}

		const float* SDFVoxelManager::GetMin() const
		{
			return m_min;
		}

		bool SDFVoxelManager::Inside(const float* world_coord) const
		{
			if (world_coord[0] < m_min[0]) return false;
			if (world_coord[1] < m_min[1]) return false;
			if (world_coord[2] < m_min[2]) return false;

			if (world_coord[0] > m_max[0]) return false;
			if (world_coord[1] > m_max[1]) return false;
			if (world_coord[2] > m_max[2]) return false;

			return true;
		}

		void SDFVoxelManager::GetCoordByIndex(unsigned index, float* out_world_coord) const
		{
			unsigned index_x = index / m_square_dimension;
			index -= index_x * m_square_dimension;

			unsigned index_y = index / m_dimension;
			index -= index_y * m_dimension;

			unsigned index_z = index;

			out_world_coord[0] = m_min[0] + index_x * m_grid_unit_length[0];
			out_world_coord[1] = m_min[1] + index_y * m_grid_unit_length[1];
			out_world_coord[2] = m_min[2] + index_z * m_grid_unit_length[2];
		}

		unsigned SDFVoxelManager::GetIndexByCoord(const float* world_coord) const
		{
			unsigned x_index = floor(world_coord[0] - m_min[0]) / m_grid_unit_length[0];
			unsigned y_index = floor(world_coord[1] - m_min[1]) / m_grid_unit_length[1];
			unsigned z_index = floor(world_coord[2] - m_min[2]) / m_grid_unit_length[2];

			return x_index * m_square_dimension + y_index * m_dimension + z_index;
		}
	}
}

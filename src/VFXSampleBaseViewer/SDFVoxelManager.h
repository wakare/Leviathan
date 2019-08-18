#pragma once

#include "SDFVoxel.h"
#include <vector>
#include <functional>

namespace Leviathan
{
	namespace Viewer
	{
		/*
		 * param 0: grid need be merged
		 * param 1: merged voxel
		 */
		typedef std::function<bool(SDFVoxel&, const SDFVoxel&)> GridMergedFunc;
		typedef std::function<void(const float*, SDFVoxel&)> SDFVoxelUpdateFunc;

		class SDFVoxelManager
		{
		public:
			SDFVoxelManager(unsigned dimension, const float* min, const float* max);
			void UpdateSDFVoxel(const float* world_coord, const SDFVoxel& voxel);
			void UpdateSDFVoxelByFunc(SDFVoxelUpdateFunc update_func);

			const std::vector<SDFVoxel>& GetAllGrids() const;
			void GetCoordByIndex(unsigned index, float* out_world_coord) const;
			unsigned GetIndexByCoord(const float* world_coord) const;
			
			const float* GetSize() const;
			const float* GetMin() const;

		private:
			bool Inside(const float* world_coord) const;
			
			GridMergedFunc m_grid_merged_func;

			float m_min[3];
			float m_max[3];
			float m_grid_length[3];

			float m_grid_unit_length[3];
			float m_inverse_grid_unit_length[3];

			unsigned m_dimension;
			unsigned m_square_dimension;

			std::vector<SDFVoxel> m_grids;
		};


	}
}
#pragma once

namespace Leviathan
{
	namespace Viewer
	{
		struct SDFVoxel
		{
			SDFVoxel()
			{
				weight = -1.0f;
			}

			float weight;
		};
	}
}
#include "LevLAttrWorldCoord.h"

namespace Leviathan
{
	namespace Scene
	{
		LevLAttrWorldCoord::LevLAttrWorldCoord(float x, float y, float z)
		{
			SetCoord(x, y, z);
		}

		LevLAttrWorldCoord::LevLAttrWorldCoord(float * coord)
		{
			SetCoord(coord);
		}

		const Eigen::Vector3f & LevLAttrWorldCoord::GetCoord() const
		{
			return m_coord;
		}

		void LevLAttrWorldCoord::SetCoord(float x, float y, float z)
		{
			m_coord[0] = x;
			m_coord[1] = y;
			m_coord[2] = z;
		}

		void LevLAttrWorldCoord::SetCoord(float * coord)
		{
			memcpy(m_coord.data(), coord, 3 * sizeof(float));
		}
	}
}



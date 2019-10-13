#include "ParticleObject3D.h"
#include <memory>

namespace Leviathan
{
	namespace Particle
	{
		ParticleObject3D::ParticleObject3D(int max_survive_tick_count, int max_survive_abs_time,
			const float* init_3D_coord, const float* init_3D_velocity, float half_length)
			: BaseParticleObject(max_survive_tick_count, max_survive_abs_time)
			, m_half_length(half_length)
		{
			memcpy(m_coord, init_3D_coord, sizeof(m_coord));
			memcpy(m_velocity, init_3D_velocity, sizeof(m_velocity));
		}
	}
}



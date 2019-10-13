#include "ParticleObject2D.h"
#include <memory>

namespace Leviathan
{
	namespace Particle
	{
		ParticleObject2D::ParticleObject2D(int max_survive_tick_count, int max_survive_abs_time, 
			const float* init_2D_coord, const float* init_2D_velocity, float half_length)
			: BaseParticleObject(max_survive_tick_count, max_survive_abs_time)
			, m_half_length(half_length)
		{
			memcpy(m_coord, init_2D_coord, sizeof(m_coord));
			memcpy(m_velocity, init_2D_velocity, sizeof(m_velocity));
		}

	}
}

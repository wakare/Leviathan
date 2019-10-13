#pragma once

#include "BaseParticleObject.h"

namespace Leviathan
{
	namespace Particle
	{
		class ParticleObject2D : public BaseParticleObject
		{
		public:
			ParticleObject2D(int max_survive_tick_count, int max_survive_abs_time, const float* init_2D_coord, const float* init_2D_velocity, float half_length);

			float& GetX() { return m_coord[0]; }
			float& GetY() { return m_coord[1]; }

			float& GetVX() { return m_velocity[0]; }
			float& GetVY() { return m_velocity[1]; }

			float& GetHalfLength() { return m_half_length; }

		private:
			float m_coord[2];
			float m_velocity[2];
			float m_half_length;
		};

	}
}


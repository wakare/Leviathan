#pragma once

#include "BaseParticleObject.h"

namespace Leviathan
{
	namespace Particle
	{
		class ParticleObject3D : public BaseParticleObject
		{
		public:
			ParticleObject3D(int max_survive_tick_count, int max_survive_abs_time, const float* init_3D_coord, const float* init_3D_velocity, float half_length);

			float& GetX() { return m_coord[0]; }
			float& GetY() { return m_coord[1]; }
			float& GetZ() { return m_coord[2]; }

			float& GetVX() { return m_velocity[0]; }
			float& GetVY() { return m_velocity[1]; }
			float& GetVZ() { return m_velocity[2]; }

			float& GetHalfLength() { return m_half_length; }

		private:
			float m_coord[3];
			float m_velocity[3];
			float m_half_length;
		};
	}
}



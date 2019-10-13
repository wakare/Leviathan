#pragma once
#include <vector>
#include "LSPtr.h"

namespace Leviathan
{
	namespace Particle
	{
		class BaseParticleObject;

		typedef std::vector<LSPtr<BaseParticleObject>> PARTICLE_SET;

		class ParticleContainer
		{
		public:
			ParticleContainer();

			bool AddParticle(LSPtr<BaseParticleObject>& particle);
			bool DeleteParticle(LSPtr<BaseParticleObject>& particle);

			const PARTICLE_SET& GetParticles() const; 

		private:
			PARTICLE_SET m_objects;
		};
	}
}



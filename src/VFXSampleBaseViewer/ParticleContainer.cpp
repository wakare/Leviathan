#include "ParticleContainer.h"

namespace Leviathan
{
	namespace Particle
	{
		ParticleContainer::ParticleContainer()
		{
		}

		bool ParticleContainer::AddParticle(LSPtr<BaseParticleObject>& particle)
		{
			m_objects.push_back(particle);
			return true;
		}

		bool ParticleContainer::DeleteParticle(LSPtr<BaseParticleObject>& particle)
		{
			particle.Reset(nullptr);
			return true;
		}

		const PARTICLE_SET& ParticleContainer::GetParticles() const
		{
			return m_objects;
		}
	}
}


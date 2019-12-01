#include "ParticleContainer.h"
#include "BaseParticleObject.h"

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

		/*bool ParticleContainer::DeleteParticle(LSPtr<BaseParticleObject>& particle)
		{
			const auto it = std::find(m_objects.begin(), m_objects.end(), [&particle](const LSPtr<BaseParticleObject>& lhs) {return lhs.Get() == particle.Get(); });
			if (it == m_objects.end())
			{
				return false;
			}

			particle.Reset(nullptr);
			m_objects.erase(it);
			return true;
		}*/

		bool ParticleContainer::ClearDiedParticles()
		{
			auto it = m_objects.begin();
			while (it != m_objects.end())
			{
				if ((*it)->HasDestroyed())
				{
					it = m_objects.erase(it);
					continue;
				}

				++it;
			}
			
			return true;
		}

		const PARTICLE_SET& ParticleContainer::GetParticles() const
		{
			return m_objects;
		}
	}
}


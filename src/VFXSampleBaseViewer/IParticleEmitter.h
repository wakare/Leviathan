#pragma once
#include "LSPtr.h"

namespace Leviathan
{
	namespace Particle
	{
		class ParticleContainer;

		class IParticleEmitter
		{
		public:
			virtual ~IParticleEmitter() = default;

			virtual void Update(ParticleContainer& particle_container) = 0;
		};
	}
}

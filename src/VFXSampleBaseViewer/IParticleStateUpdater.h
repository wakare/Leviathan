#pragma once

namespace Leviathan
{
	namespace Particle
	{
		class BaseParticleObject;

		class IParticleStateUpdater
		{
		public:
			virtual void UpdateParticleState(BaseParticleObject& particle_object) = 0;
		};
	}
}


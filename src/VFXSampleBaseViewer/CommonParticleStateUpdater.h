#pragma once
#include "IParticleStateUpdater.h"

namespace Leviathan
{
	namespace Particle
	{
		class CommonParticleStateUpdater : public IParticleStateUpdater
		{
		public:
			void UpdateParticleState(BaseParticleObject& particle_object) override;
		};
	}
}


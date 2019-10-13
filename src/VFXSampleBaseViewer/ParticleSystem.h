#pragma once
#include "LSPtr.h"
#include "LevTimer.h"

namespace Leviathan
{
	namespace Particle
	{
		class BaseParticleObject;
		class ParticleContainer;
		class IParticleStateUpdater;
		class IParticleEmitter;

		class ParticleSystem
		{
		public:
			ParticleSystem();

			void SetParticleUpdater(LSPtr<IParticleStateUpdater> state_updater);
			void SetParticleEmitter(LSPtr<IParticleEmitter> emitter);

			ParticleContainer& GetContainer();

			virtual void Update();

		private:
			void _first_update();
			LevTimer m_timer;

			bool m_first_updated;
			LSPtr<ParticleContainer> m_container;
			LSPtr<IParticleStateUpdater> m_state_updater;
			LSPtr<IParticleEmitter> m_emitter;
		};
	}
}

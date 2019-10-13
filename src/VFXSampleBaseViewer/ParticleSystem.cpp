#include "ParticleSystem.h"
#include "BaseParticleObject.h"
#include "LevTimer.h"
#include "ParticleContainer.h"
#include "IParticleStateUpdater.h"
#include "IParticleEmitter.h"

namespace Leviathan
{
	namespace Particle
	{
		ParticleSystem::ParticleSystem()
			: m_container(new ParticleContainer)
			, m_timer(0, nullptr)
			, m_first_updated(false)
			, m_state_updater(nullptr)
			, m_emitter(nullptr)
		{
		}

		void ParticleSystem::SetParticleUpdater(LSPtr<IParticleStateUpdater> state_updater)
		{
			m_state_updater = state_updater;
		}

		void ParticleSystem::SetParticleEmitter(LSPtr<IParticleEmitter> emitter)
		{
			m_emitter = emitter;
		}

		ParticleContainer& ParticleSystem::GetContainer()
		{
			return *m_container;
		}

		void ParticleSystem::Update()
		{
			if (!m_first_updated)
			{
				_first_update();
				return;
			}

			const auto last_time = m_timer.GetLastTime();
			m_timer.UpdateCurrentTickTime();

			const auto interval_time = m_timer.GetLastTime() - last_time;

			if (m_emitter)
			{
				m_emitter->Update(*m_container);
			}

			const auto& particles = m_container->GetParticles();

			for (auto& particle : particles)
			{
				if (!particle.Get())
				{
					continue;
				}

				if (m_state_updater)
				{
					m_state_updater->UpdateParticleState(*particle);
				}

				auto& remain_tick_count = particle->GetMaxSurviveTickCount();
				if (remain_tick_count > 0)
				{
					--remain_tick_count;
					particle->FrameTick();
				}

				auto& remain_abs_time = particle->GetMaxSurviveAbsTime();
				if (remain_abs_time > 0)
				{
					particle->TimeTick(interval_time);
					remain_abs_time -= interval_time;
				}

				if (remain_tick_count < 0 && remain_abs_time < 0)
				{
					particle->BeDestroy();
				}
			}
		}

		void ParticleSystem::_first_update()
		{
			m_timer.UpdateCurrentTickTime();
			m_first_updated = true;
		}
	}
}



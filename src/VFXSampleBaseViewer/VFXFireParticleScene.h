#pragma once

#include "VFXCommonScene.h"

namespace Leviathan
{
	namespace Particle
	{
		class ParticleSystem;
	}

	namespace Viewer
	{
		class VFXFireParticleScene : public VFXCommonScene
		{
		public:
			VFXFireParticleScene();

		private:
			void _init();
			void _update();

			LSPtr<LevSceneNode> m_root;
			std::vector<LSPtr<LevSceneNode>> delete_particles;
			LSPtr<Particle::ParticleSystem> m_fire_particle_system;
		};
	}
}

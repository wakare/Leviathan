#include "VFXFireParticleScene.h"
#include <utility>
#include <utility>
#include "LevSceneObject.h"
#include "LevSceneNode.h"
#include "ParticleSystem.h"
#include "ParticleObject2D.h"
#include "IParticleEmitter.h"
#include "LevSceneUtil.h"
#include "ParticleContainer.h"
#include "LevTextureUniform.h"
#include "LevRAttrShaderProgram.h"
#include "ParticleProgram.h"
#include "LevSceneData.h"

namespace Leviathan
{
	namespace Particle
	{
		class FireParticle : public ParticleObject2D
		{
		public:
			FireParticle(int tick_count, int life_time, const float* init_coord, const float* init_velocity, float half_length, LSPtr<LevTextureUniform> texture_uniform);

			void FrameTick() override;
			void TimeTick(unsigned delta_time) override;
			void BeDestroy() override;

			LSPtr<LevSceneNode> GetParticleSceneNode();

		private:
			void _init_scene_node();
			void _update_scene_node();

			LSPtr<LevTextureUniform> m_texture_uniform;
			LSPtr<LevSceneNode> m_particle_scene_node;
		};

		inline FireParticle::FireParticle(int tick_count, int life_time, const float* init_coord, const float* init_velocity, float half_length, LSPtr<LevTextureUniform> texture_uniform)
			: ParticleObject2D(tick_count, life_time, init_coord, init_velocity, half_length)
			, m_texture_uniform(std::move(texture_uniform))
			, m_particle_scene_node(nullptr)
		{
			_init_scene_node();
		}

		inline void FireParticle::FrameTick()
		{
			GetX() += GetVX();
			GetY() += GetVY();

			_update_scene_node();
		}

		inline void FireParticle::TimeTick(unsigned delta_time)
		{
			GetX() += delta_time * GetVX();
			GetY() += delta_time * GetVY();

			_update_scene_node();
		}

		inline void FireParticle::BeDestroy()
		{
			LogLine("Particle " << m_id << " has been destroy!!");
		}

		LSPtr<LevSceneNode> FireParticle::GetParticleSceneNode()
		{
			return m_particle_scene_node;
		}

		void FireParticle::_init_scene_node()
		{
			const float plane_node_data[] =
			{
				GetX() - GetHalfLength(), GetY() - GetHalfLength(), 0.0f,
				GetX() - GetHalfLength(), GetY() + GetHalfLength(), 0.0f,
				GetX() + GetHalfLength(), GetY() + GetHalfLength(), 0.0f,
				GetX() + GetHalfLength(), GetY() - GetHalfLength(), 0.0f,
			};

			LevSceneUtil::GeneratePlaneNode(plane_node_data, plane_node_data + 3, plane_node_data + 6, plane_node_data + 9, m_particle_scene_node);
		}

		void FireParticle::_update_scene_node()
		{
			const float plane_node_data[] =
			{
				GetX() - GetHalfLength(), GetY() - GetHalfLength(), 0.0f,
				GetX() - GetHalfLength(), GetY() + GetHalfLength(), 0.0f,
				GetX() + GetHalfLength(), GetY() + GetHalfLength(), 0.0f,
				GetX() + GetHalfLength(), GetY() - GetHalfLength(), 0.0f,
			};

			LevSceneUtil::GeneratePlaneNode(plane_node_data, plane_node_data + 3, plane_node_data + 6, plane_node_data + 9, m_particle_scene_node);
		}

		class FireParticleEmitter : public IParticleEmitter
		{
		public:
			FireParticleEmitter(unsigned emit_speed, LSPtr<LevTextureUniform> particle_texture);

			void Update(ParticleContainer& particle_container) override;

		private:
			unsigned m_emit_num_per_tick;

			LSPtr<LevTextureUniform> m_texture;
		};

		inline FireParticleEmitter::FireParticleEmitter(unsigned emit_speed, LSPtr<LevTextureUniform> particle_texture)
			: m_emit_num_per_tick(emit_speed)
			, m_texture(particle_texture)
		{

		}

		inline void FireParticleEmitter::Update(ParticleContainer& particle_container)
		{
			for (unsigned i = 0 ; i < m_emit_num_per_tick; ++i)
			{
				const int tick_count = RAND_RANGE(10, 20);
				const int life_time = -1;

				const float birth_coord[] = { RAND_RANGE(-0.1f, 0.1f), RAND_RANGE(-0.3f, -0.1f)};
				const float velocity[] = { RAND_RANGE(-0.01f, 0.01f), RAND_RANGE(-0.01f, 0.01f) };

				LSPtr<BaseParticleObject> fire_particle = new FireParticle(tick_count, life_time, birth_coord, velocity, 0.02f, m_texture);
				particle_container.AddParticle(fire_particle);
			}
		}
	}

	namespace Viewer
	{
		VFXFireParticleScene::VFXFireParticleScene()
			: m_root(new LevSceneNode(new LevSceneObject(ELSOT_EMPTY)))
			, m_fire_particle_system(new Particle::ParticleSystem)
		{
			_init();
		}

		void VFXFireParticleScene::_init()
		{
			GetSceneData().AddSceneNodeToRoot(m_root);

			m_root->GetNodeData()->SetUpdatedCallback([&](LevSceneObject&) {m_fire_particle_system->Update(); _update(); });

			LSPtr<LevShaderProgram> program = new LevShaderProgram;
			program->m_vert_shader = fire_vert;
			program->m_frag_shader = fire_frag;
			LSPtr<LevRAttrShaderProgram> attr_program = new LevRAttrShaderProgram;
			attr_program->SetShaderProgram(program);

			m_root->GetNodeData()->AddAttribute(attr_program);

			LSPtr<LevTextureUniform> texture_uniform = new LevTextureUniform("Particle_Tex");
			LSPtr<RAIIBufferData> tex_data = new RAIIBufferData(2 * 2 * sizeof(float));
			/*auto data = tex_data->GetArrayData();*/

			LSPtr<LevTextureObject> texture_object = new LevTextureObject(ELTT_2D_COLOR_TEXTURE, 2, 2, 1, tex_data);
			texture_uniform->SetUniformData(texture_object);

			LSPtr<Particle::IParticleEmitter> emitter = new Particle::FireParticleEmitter(10, nullptr);
			m_fire_particle_system->SetParticleEmitter(emitter);
			//m_fire_particle_system->SetParticleUpdater()
		}

		void VFXFireParticleScene::_update()
		{
			for (auto& child : m_root->GetChildren())
			{
				child->GetNodeData()->SetState(ELSOS_DELETED);
			}

			auto& particles = m_fire_particle_system->GetContainer().GetParticles();

			for (auto& particle : particles)
			{
				auto fire_particle = particle.To<Particle::FireParticle>();
				m_root->AddChild(fire_particle->GetParticleSceneNode());
			}
		}
	}
}

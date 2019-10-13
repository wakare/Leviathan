#pragma once

namespace Leviathan
{
	namespace Particle
	{
		typedef unsigned PARTICLE_HANDLE;

		class BaseParticleObject
		{
		public:
			virtual ~BaseParticleObject() = default;
			BaseParticleObject(int max_survive_tick_count, int max_survive_abs_time);

			virtual void FrameTick() = 0;
			virtual void TimeTick(unsigned delta_time) = 0;
			virtual void BeDestroy() = 0;

			int& GetMaxSurviveTickCount();
			int& GetMaxSurviveAbsTime();

			void SetTranslation(const float* translation);
			void SetRotationAngle(float angle);

		protected:
			int m_max_survive_tick_count;
			/*
			 * Absolute time count by microsecond
			 */
			int m_max_survive_absolute_time;

			PARTICLE_HANDLE m_id;
			bool m_need_be_destroy;

			float m_translation[2];
			float m_rotation_angle;
		};
	}
}



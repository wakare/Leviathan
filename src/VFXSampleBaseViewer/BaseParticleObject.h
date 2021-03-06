﻿#pragma once

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
			void Destroy();

			bool HasDestroyed() const;
			
			int& GetMaxSurviveTickCount();
			int& GetMaxSurviveAbsTime();

			void SetTranslation(const float* translation);
			void SetRotationAngle(float angle);

		protected:
			virtual void DestroyImpl() = 0;
			
			int m_max_survive_tick_count;
			/*
			 * Absolute time count by microsecond
			 */
			int m_max_survive_absolute_time;

			PARTICLE_HANDLE m_id;
			bool m_destroyed;

			float m_translation[2];
			float m_rotation_angle;
		};
	}
}



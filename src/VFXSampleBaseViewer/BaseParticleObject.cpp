#include "BaseParticleObject.h"
#include "LevTokenDispatch.h"

namespace Leviathan
{
	namespace Particle
	{
		BaseParticleObject::BaseParticleObject(int max_survive_tick_count, int max_survive_abs_time)
			: m_id(LevTokenDispatch<BaseParticleObject, PARTICLE_HANDLE>::GetIncrementToken())
			, m_max_survive_tick_count(max_survive_tick_count)
			, m_max_survive_absolute_time(max_survive_abs_time)
			, m_destroyed(false)
		{

		}

		void BaseParticleObject::Destroy()
		{
			DestroyImpl();
			m_destroyed = true;
		}

		bool BaseParticleObject::HasDestroyed() const
		{
			return m_destroyed;
		}

		int& BaseParticleObject::GetMaxSurviveTickCount()
		{
			return m_max_survive_tick_count;
		}

		int& BaseParticleObject::GetMaxSurviveAbsTime()
		{
			return m_max_survive_absolute_time;
		}

		void BaseParticleObject::SetTranslation(const float* translation)
		{
			memcpy(m_translation, translation, sizeof(m_translation));
		}

		void BaseParticleObject::SetRotationAngle(float angle)
		{
			m_rotation_angle = angle;
		}
	}
}


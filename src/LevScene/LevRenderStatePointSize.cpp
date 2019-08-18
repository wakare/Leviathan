#include "LevRenderStatePointSize.h"

namespace  Leviathan
{
	namespace Scene
	{
		LevRenderStatePointSize::LevRenderStatePointSize(unsigned point_size)
			: m_point_size(point_size)
		{

		}

		LevRenderStateType LevRenderStatePointSize::GetRenderStateType() const
		{
			return ELRST_POINT_SIZE;
		}

		void LevRenderStatePointSize::SetPointSize(unsigned point_size)
		{
			m_point_size = point_size;
		}

		unsigned LevRenderStatePointSize::GetPointSize() const
		{
			return m_point_size;
		}
	}
}
#include "OpenGLRStatePointSize.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRStatePointSize::OpenGLRStatePointSize()
			: m_point_size(1)
		{
		}

		OpenGLRStatePointSize::OpenGLRStatePointSize(GLuint point_size)
			: m_point_size(point_size)
		{
		}

		OpenGLRStatePointSize* OpenGLRStatePointSize::ToPointSize()
		{
			return this;
		}

		OpenGLRenderStateType OpenGLRStatePointSize::GetRenderStateType() const
		{
			return EOGLRST_POINT_SIZE;
		}

		void OpenGLRStatePointSize::SetPointSize(GLuint point_size)
		{
			m_point_size = point_size;
		}

		GLuint OpenGLRStatePointSize::GetPointSize() const
		{
			return m_point_size;
		}

		void OpenGLRStatePointSize::Apply()
		{
			glPointSize(m_point_size);
		}

		void OpenGLRStatePointSize::UnApply()
		{
			if (m_last_render_state)
			{
				auto* last_point_size = m_last_render_state->ToPointSize();
				LEV_ASSERT(last_point_size);

				last_point_size->Apply();
			}
			else
			{
				glPointSize(1);
			}
		}
	}
}


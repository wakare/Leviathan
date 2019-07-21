#include "OpenGLRenderStateDepthFunc.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderStateDepthFunc::OpenGLRenderStateDepthFunc(const Scene::LevRenderStateDepthFunc & depth_func)
		{
			switch (depth_func.GetDepthFunc())
			{

			case Scene::ELDF_LESS:
				m_depth_func_value = GL_LESS;
				break;

			case Scene::ELDF_LEQUAL:
				m_depth_func_value = GL_LEQUAL;
				break;

			case Scene::ELDF_EQUAL:
				m_depth_func_value = GL_EQUAL;
				break;

			case Scene::ELDF_NOTEQUAL:
				m_depth_func_value = GL_NOTEQUAL;
				break;

			case Scene::ELDF_GEQUAL:
				m_depth_func_value = GL_GEQUAL;
				break;

			case Scene::ELDF_GREATER:
				m_depth_func_value = GL_GREATER;
				break;

			case Scene::ELDF_NEVER:
				m_depth_func_value = GL_NEVER;
				break;

			case Scene::ELDF_ALWAYS:
				m_depth_func_value = GL_ALWAYS;
				break;

			default:
				break;
			}
		}

		void OpenGLRenderStateDepthFunc::ApplyState()
		{
			glGetIntegerv(GL_DEPTH_FUNC, &m_last_enum_value);
			m_last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);

			glDepthFunc(m_depth_func_value);
			glEnable(GL_DEPTH_TEST);
		}

		void OpenGLRenderStateDepthFunc::UnApplyState()
		{
			glDepthFunc(m_last_enum_value);

			if (!m_last_enable_depth_test)
			{
				glDisable(GL_DEPTH_TEST);
			}
		}
	}
}
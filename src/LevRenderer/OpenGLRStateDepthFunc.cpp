#include "OpenGLRStateDepthFunc.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRStateDepthFunc::OpenGLRStateDepthFunc(const Scene::LevRenderStateDepthFunc & depth_func)
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

		OpenGLRStateDepthFunc* OpenGLRStateDepthFunc::ToDepthFunc()
		{
			return this;
		}

		OpenGLRenderStateType OpenGLRStateDepthFunc::GetRenderStateType() const
		{
			return EOGLRST_DEPTH_FUNC;
		}

		void OpenGLRStateDepthFunc::Apply()
		{
			glEnable(GL_DEPTH_TEST);
			glDepthMask(true);
			glDepthFunc(m_depth_func_value);
		}

		void OpenGLRStateDepthFunc::UnApply()
		{
			if (m_last_render_state)
			{
				auto* last_depth_func = m_last_render_state->ToDepthFunc();
				last_depth_func->Apply();
			}
			else
			{
				glDepthFunc(GL_LESS);
			}
		}
	}
}
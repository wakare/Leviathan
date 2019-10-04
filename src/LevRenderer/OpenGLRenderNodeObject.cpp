#include "OpenGLRenderNodeObject.h"
#include "OpenGLRenderEntry.h"
#include "OpenGLRenderStateManager.h"
#include "OpenGLProgramUniformManager.h"
#include "OpenGLFrameBufferObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderNodeObject::OpenGLRenderNodeObject(LSPtr<OpenGLRenderEntry> object)
			: m_object(object)
		{
			LEV_ASSERT(object);
		}

		bool OpenGLRenderNodeObject::Valid() const
		{
			return m_object.Get();
		}

		unsigned OpenGLRenderNodeObject::GetID() const
		{
			return m_object->GetID();
		}

		void OpenGLRenderNodeObject::ApplyRenderState(OpenGLRenderStateManager& render_state_manager)
		{
			auto& render_states = m_object->GetRenderState();
			for (auto& state : render_states)
			{
				render_state_manager.ApplyRenderState(state);
			}
		}

		void OpenGLRenderNodeObject::UnApplyRenderState(OpenGLRenderStateManager& render_state_manager)
		{
			/*auto& render_states = m_object->GetRenderState();
			for (auto& state : render_states)
			{
				render_state_manager.UnApplyRenderState(state);
			}*/
		}

		void OpenGLRenderNodeObject::ApplyUniform(OpenGLProgramUniformManager& uniform_manager)
		{
			auto& uniforms = m_object->GetUniforms();
			for (auto& uniform : uniforms)
			{
				uniform_manager.ApplyUniform(uniform);
			}
		}

		void OpenGLRenderNodeObject::UnApplyUniform(OpenGLProgramUniformManager& uniform_manager)
		{
			/*auto& uniforms = m_object->GetUniforms();
			for (auto& uniform : uniforms)
			{
				uniform_manager.ApplyUniform(uniform);
			}*/
		}

		void OpenGLRenderNodeObject::ApplyFrameBufferObject()
		{
			LSPtr<OpenGLFrameBufferObject> frame_buffer_object = m_object->GetFrameBufferObject();
			if (frame_buffer_object.Get())
			{
				frame_buffer_object->Apply();
			}
		}

		void OpenGLRenderNodeObject::UnApplyFrameBufferObject()
		{
			LSPtr<OpenGLFrameBufferObject> frame_buffer_object = m_object->GetFrameBufferObject();
			if (frame_buffer_object.Get())
			{
				frame_buffer_object->UnApply();
			}
		}

		void OpenGLRenderNodeObject::Render(GLuint shader_program)
		{
			m_object->Render(shader_program);
		}
	}
}
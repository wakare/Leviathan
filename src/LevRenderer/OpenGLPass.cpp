#include "OpenGLPass.h"
#include "OpenGLRenderEntry.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLProgramUniformManager.h"
#include "OpenGLRenderNodeVisitor.h"
#include "OpenGLRenderNode.h"
#include "OpenGLRenderStateManager.h"
#include "OpenGLResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLPass::OpenGLPass(OpenGLRenderResourceManager& resource_manager, LSPtr<OpenGLShaderProgram> shader_program, LSPtr<OpenGLProgramUniformManager> pass_uniform_manager, OpenGLRenderStateManager& render_state_manager)
			: IOpenGLRenderResource(resource_manager)
			, m_id(shader_program->GetID())
			, m_render_state_manager(render_state_manager)
			, m_shader_program(shader_program)
			, m_pass_uniform_manager(pass_uniform_manager)
			, m_render_visitor(new OpenGLRenderNodeVisitor(shader_program->GetShaderProgram(), m_render_state_manager, *m_pass_uniform_manager))
		{

		}

		bool OpenGLPass::Render(OpenGLRenderTree& render_tree)
		{
			// Set GLProgram
			auto program = m_shader_program->GetShaderProgram();
			IOR_PUSH_ASYNC_RENDER_COMMAND(glUseProgram(program));
			
			m_render_visitor->Apply(render_tree.GetRoot());

			// ResetProgram
			IOR_PUSH_ASYNC_RENDER_COMMAND(glUseProgram(0));

			return true;
		}

		unsigned OpenGLPass::GetID() const
		{
			return m_id;
		}

		Leviathan::Renderer::OpenGLRenderNodeVisitor& OpenGLPass::GetRenderVisitor()
		{
			return *m_render_visitor;
		}

	}
}

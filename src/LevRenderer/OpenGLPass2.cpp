#include "OpenGLPass2.h"
#include "OpenGLObject2.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLPass2::OpenGLPass2(LPtr<OpenGLShaderProgram> shader_program)
			: m_id(shader_program->GetID())
			, m_shader_program(shader_program)
			, m_render_visitor(new OpenGLRenderNodeVisitor(shader_program->GetShaderProgram()))
		{

		}

		bool OpenGLPass2::Render(OpenGLRenderTree& render_tree)
		{
			// Set GLProgram
			auto program = m_shader_program->GetShaderProgram();
			glUseProgram(program);

			m_render_visitor->Apply(render_tree.GetRoot());

			// ResetProgram
			glUseProgram(0);

			return true;
		}

		unsigned OpenGLPass2::GetID() const
		{
			return m_id;
		}

		Leviathan::Renderer::OpenGLRenderNodeVisitor& OpenGLPass2::GetRenderVisitor()
		{
			return *m_render_visitor;
		}

	}
}

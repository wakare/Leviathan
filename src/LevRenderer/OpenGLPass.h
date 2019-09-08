#pragma once

#include <map>
#include "LSPtr.h"
#include "NodeVisitor.h"
#include "OpenGLRenderTree.h"


namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderEntry;
		class OpenGLShaderProgram;
		class OpenGLResourceManager;
		class OpenGLRenderStateManager;
		class OpenGLUniformManager;
		class OpenGLRenderNodeVisitor;
		
		class OpenGLPass
		{
		public:
			OpenGLPass(LSPtr<OpenGLShaderProgram> shader_program, OpenGLRenderStateManager& render_state_manager);
			bool Render(OpenGLRenderTree& render_tree);

			unsigned GetID() const;
			OpenGLRenderNodeVisitor& GetRenderVisitor();

		private:
			const unsigned m_id;

			OpenGLRenderStateManager& m_render_state_manager;
			
			LSPtr<OpenGLShaderProgram> m_shader_program;
			LSPtr<OpenGLUniformManager> m_pass_uniform_manager;
			LSPtr<OpenGLRenderNodeVisitor> m_render_visitor;
		};
	}
}

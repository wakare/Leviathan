#pragma once

#include <map>
#include "LPtr.h"
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
			OpenGLPass(LPtr<OpenGLShaderProgram> shader_program, OpenGLRenderStateManager& render_state_manager);
			bool Render(OpenGLRenderTree& render_tree);

			unsigned GetID() const;
			OpenGLRenderNodeVisitor& GetRenderVisitor();

		private:
			const unsigned m_id;

			OpenGLRenderStateManager& m_render_state_manager;
			
			LPtr<OpenGLShaderProgram> m_shader_program;
			LPtr<OpenGLUniformManager> m_pass_uniform_manager;
			LPtr<OpenGLRenderNodeVisitor> m_render_visitor;
		};
	}
}

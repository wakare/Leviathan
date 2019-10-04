#pragma once

#include <map>
#include "LSPtr.h"
#include "NodeVisitor.h"
#include "OpenGLRenderTree.h"
#include "IOpenGLRenderResource.h"


namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderEntry;
		class OpenGLShaderProgram;
		class OpenGLResourceManager;
		class OpenGLRenderStateManager;
		class OpenGLProgramUniformManager;
		class OpenGLRenderNodeVisitor;
		
		class OpenGLPass : public IOpenGLRenderResource
		{
		public:
			OpenGLPass(OpenGLRenderResourceManager& resource_manager, LSPtr<OpenGLShaderProgram> shader_program, LSPtr<OpenGLProgramUniformManager> pass_uniform_manager, OpenGLRenderStateManager& render_state_manager);
			bool Render(OpenGLRenderTree& render_tree);
				
			unsigned GetID() const;
			OpenGLRenderNodeVisitor& GetRenderVisitor();

		private:
			const unsigned m_id;

			OpenGLRenderStateManager& m_render_state_manager;
			
			LSPtr<OpenGLShaderProgram> m_shader_program;
			LSPtr<OpenGLProgramUniformManager> m_pass_uniform_manager;
			LSPtr<OpenGLRenderNodeVisitor> m_render_visitor;
		};
	}
}

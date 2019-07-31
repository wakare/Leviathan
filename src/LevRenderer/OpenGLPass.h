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
		/*
			Render node visitor
		*/
		class OpenGLRenderNodeVisitor : public NodeVisitor<OpenGLRenderNodeObject>
		{
		public:
			OpenGLRenderNodeVisitor(GLuint shader_program, OpenGLRenderStateManager& render_state_manager, OpenGLUniformManager& uniform_manager)
				: m_shader_program(shader_program)
				, m_uniform_manager(uniform_manager)
				, m_render_state_manager(render_state_manager)
			{
			}

			void Apply(Node<OpenGLRenderNodeObject>& node) override
			{
				auto node_data = node.GetNodeData();
				if (node_data && node_data->Valid())
				{
					/*
					 * Set render states && uniforms
					 */
					node_data->ApplyUniform(m_uniform_manager);
					node_data->ApplyRenderState(m_render_state_manager);
					node_data->Render(m_shader_program);
				}

				for (auto& child : node.GetChildren())
				{
					Apply(*child);
				}
			}

			void Apply(const Node<OpenGLRenderNodeObject>& node) override
			{
				LEV_ASSERT(false);
			}

		private:
			GLuint m_shader_program;

			OpenGLUniformManager& m_uniform_manager;
			OpenGLRenderStateManager& m_render_state_manager;
		};

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
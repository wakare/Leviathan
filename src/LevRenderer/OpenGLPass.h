#pragma once

#include <map>
#include "LPtr.h"
#include "NodeVisitor.h"
#include "OpenGLRenderTree.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLObject;
		class OpenGLShaderProgram;
		class OpenGLResourceManager;

		/*
			Render node visitor
		*/
		class OpenGLRenderNodeVisitor : public NodeVisitor<OpenGLRenderNodeObject>
		{
		public:
			OpenGLRenderNodeVisitor(GLuint shader_program)
				: m_shader_program(shader_program)
			{
			}

			virtual void Apply(Node<OpenGLRenderNodeObject>& node)
			{
				auto node_data = node.GetNodeData();
				if (node_data && node_data->Valid())
				{
					node_data->Render(m_shader_program);
				}

				for (auto& child : node.GetChildren())
				{
					Apply(*child);
				}
			}

			virtual void Apply(const Node<OpenGLRenderNodeObject>& node)
			{
				LEV_ASSERT(false);
			}

		private:
			GLuint m_shader_program;
		};

		class OpenGLPass
		{
		public:
			OpenGLPass(LPtr<OpenGLShaderProgram> shader_program);
			bool Render(OpenGLRenderTree& render_tree);

			unsigned GetID() const;
			OpenGLRenderNodeVisitor& GetRenderVisitor();

		private:
			const unsigned m_id;
			LPtr<OpenGLShaderProgram> m_shader_program;
			LPtr<OpenGLRenderNodeVisitor> m_render_visitor;
		};
	}
}
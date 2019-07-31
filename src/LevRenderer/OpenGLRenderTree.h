#pragma once

#include "Node.h"
#include <GL/glew.h>
#include <map>

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderEntry;
		class OpenGLShaderProgram;
		class OpenGLRenderStateManager;
		class OpenGLUniformManager;

		class OpenGLRenderNodeObject
		{
		public:
			OpenGLRenderNodeObject(LPtr<OpenGLRenderEntry> object);
			bool Valid() const;
			unsigned GetID() const;

			void ApplyRenderState(OpenGLRenderStateManager& render_state_manager);
			void ApplyUniform(OpenGLUniformManager& uniform_manager);

			void Render(GLuint shader_program);

		private:
			LPtr<OpenGLRenderEntry> m_object;
		};

		class OpenGLRenderNode : public Node<OpenGLRenderNodeObject>
		{
		public:
			OpenGLRenderNode(LPtr<OpenGLRenderNodeObject> object);
			virtual void Accept(NodeVisitor<OpenGLRenderNodeObject>& nodeVisitor);
		};

		/*
			One OpenGLPass mapping one OpenGLRenderTree		
		*/
		class OpenGLRenderTree
		{
		public:
			OpenGLRenderTree(LPtr<OpenGLRenderStateManager> render_state_manager);
			bool AddNodeToRoot(LPtr<OpenGLRenderNode> node);
			bool ReplaceNode(LPtr<OpenGLRenderNode> node);
			bool RemoveNode(unsigned handle);

			OpenGLRenderNode& GetRoot();

		private:
			LPtr<OpenGLRenderNode> m_root;
			LPtr<OpenGLRenderStateManager> m_render_state_manager;

			std::map<unsigned, LPtr<OpenGLRenderNode>> m_nodes;
		};
	}
}

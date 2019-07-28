#pragma once

#include "Node.h"
#include <gl/glew.h>
#include <map>

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderEntry;
		class OpenGLShaderProgram;

		class OpenGLRenderNodeObject
		{
		public:
			OpenGLRenderNodeObject(LPtr<OpenGLRenderEntry> object);
			bool Valid() const;
			unsigned GetID() const;
			void PreRender(GLuint shader_program);
			void Render(GLuint shader_program);
			void PostRender(GLuint shader_program);

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
			OpenGLRenderTree();
			bool AddNodeToRoot(LPtr<OpenGLRenderNode> node);
			bool ReplaceNode(LPtr<OpenGLRenderNode> node);
			bool RemoveNode(unsigned handle);

			OpenGLRenderNode& GetRoot();

		private:
			LPtr<OpenGLRenderNode> m_root;

			std::map<unsigned, LPtr<OpenGLRenderNode>> m_nodes;
		};
	}
}

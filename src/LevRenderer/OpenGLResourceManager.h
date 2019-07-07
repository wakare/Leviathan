#pragma once

#include <map>
#include <vector>
#include "LPtr.h"
#include "NodeVisitor.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevRAttrShaderProgram;
	}

	namespace Renderer
	{
		class OpenGLObject;
		class OpenGLObject2;
		class OpenGLPass2;
		class OpenGLRenderTree;
		class OpenGLRenderNodeObject;

		typedef int RenderTreeID;
		class OpenGLResourceManager
		{
		public:
			OpenGLResourceManager();
			RenderTreeID GetOrCreateRenderTree(const Scene::LevRAttrShaderProgram& shader_program);
			bool AddGLObject(RenderTreeID handle, LPtr<OpenGLObject2> pObject);
			bool ReplaceGLObject(RenderTreeID handle, LPtr<OpenGLObject2> pObjects);
			bool RemoveResource(RenderTreeID handle, unsigned object_id);

			bool Render();

		private:
			std::map<RenderTreeID, LPtr<OpenGLPass2>> m_render_pass;
			std::map<RenderTreeID, LPtr<OpenGLRenderTree>> m_render_trees;
		};
	}
}
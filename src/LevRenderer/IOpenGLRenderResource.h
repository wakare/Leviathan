#pragma once

#include "IOpenGLResource.h"
#include "OpenGLRenderResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLRenderResource : public IOpenGLResource
		{
		public:
			IOpenGLRenderResource(OpenGLRenderResourceManager& render_entry_manager)
				: IOpenGLResource(render_entry_manager.GetResourceManager())
				, m_render_entry_manager(render_entry_manager)
			{
				
			}

			IOpenGLRenderResource* ToOpenGLRenderEntry() override { return this; }

		protected:
			OpenGLRenderResourceManager& m_render_entry_manager;
		};
	}
}

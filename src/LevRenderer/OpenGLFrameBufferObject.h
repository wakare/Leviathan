#pragma once
#include <GL/glew.h>
#include <map>
#include "LevFrameBufferObject.h"
#include "IOpenGLBufferObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLFrameBufferObject
		{
		public:
			OpenGLFrameBufferObject(const Scene::LevFrameBufferObject& frame_buffer);
			~OpenGLFrameBufferObject();

			void Apply();
			void UnApply();

		private:
			bool _init_frame_object();

			GLuint m_frame_buffer_object;
			std::map<Scene::LevFrameAttachmentType, LPtr<IOpenGLBufferObject>> m_attachments;
		};
	}
}


#pragma once
#include <GL/glew.h>
#include <map>
#include "LevFrameBufferObject.h"
#include "IOpenGLBufferObject.h"
#include <vector>

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLFrameBufferObject : public IOpenGLBufferObject
		{
		public:
			OpenGLFrameBufferObject(OpenGLObjectManager& object_manager, const Scene::LevFrameBufferObject& frame_buffer);
			~OpenGLFrameBufferObject();

			OpenGLBufferBufferType GetBufferObjectType() const override;

			void Apply();
			void UnApply();

		private:
			bool _init_frame_object();

			GLuint m_frame_buffer_object;
			std::vector<GLenum> m_attachment_enums;
			std::map<Scene::LevFrameAttachmentType, LSPtr<IOpenGLBufferObject>> m_attachments;
		};
	}
}


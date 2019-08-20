#include "OpenGLFrameBufferObject.h"
#include "GlobalDef.h"
#include "LevFrameBufferObject.h"
#include "LevAttachment.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLFrameBufferObject::OpenGLFrameBufferObject(const Scene::LevFrameBufferObject& frame_buffer)
			: m_frame_buffer(frame_buffer)
		{
			glGenFramebuffers(1, &m_frame_buffer_object);
			glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object);

			const auto& frame_buffer_attachments = frame_buffer.GetAttachments();

			for (const auto& attachment : frame_buffer_attachments)
			{
				switch (attachment.second->GetAttachmentType())
				{
				case Scene::ELAT_TEXTURE_OBJECT:
					
					break;

				default:
					LogLine("[WARN] Unknown attachment type.");
					break;
				}
			}

			LEV_ASSERT(glCheckFramebufferStatus(m_frame_buffer_object) == GL_FRAMEBUFFER_COMPLETE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		OpenGLFrameBufferObject::~OpenGLFrameBufferObject()
		{
			glDeleteFramebuffers(1, &m_frame_buffer_object);
		}

		void OpenGLFrameBufferObject::Apply()
		{

		}

		void OpenGLFrameBufferObject::UnApply()
		{

		}
	}
}

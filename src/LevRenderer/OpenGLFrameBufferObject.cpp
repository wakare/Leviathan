#include "OpenGLFrameBufferObject.h"
#include "GlobalDef.h"
#include "LevFrameBufferObject.h"
#include "LevAttachment.h"
#include "OpenGLTextureBufferObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLFrameBufferObject::OpenGLFrameBufferObject(const Scene::LevFrameBufferObject& frame_buffer)
			: m_frame_buffer_object(0)
		{
			const auto& frame_buffer_attachments = frame_buffer.GetAttachments();

			for (const auto& attachment : frame_buffer_attachments)
			{
				const auto& attach_target_type = attachment.first;

				switch (attachment.second->GetAttachmentType())
				{
				case Scene::ELAT_TEXTURE_OBJECT:
				{
					const Scene::LevTextureObject* texture = attachment.second->ToLevTextureObject();
					LEV_ASSERT(texture);

						/*
						 * Should get texture object bu OpenGL Object Manager
						 */
					m_attachments[attach_target_type].Reset(new OpenGLTextureBufferObject(*texture));
					break;
				}
					
				default:
					LogLine("[WARN] Unknown attachment type.");
					break;
				}
			}

			const auto inited = _init_frame_object();
			LEV_ASSERT(inited);
		}

		OpenGLFrameBufferObject::~OpenGLFrameBufferObject()
		{
			glDeleteFramebuffers(1, &m_frame_buffer_object);
		}

		void OpenGLFrameBufferObject::Apply()
		{
			assert(!m_attachment_enums.empty());

			glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object);
			glDrawBuffers(m_attachment_enums.size(), &m_attachment_enums[0]);

			/*
			 * TODO: Provide interface for user to set default clear operation
			 */
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OpenGLFrameBufferObject::UnApply()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		bool OpenGLFrameBufferObject::_init_frame_object()
		{
			glGenFramebuffers(1, &m_frame_buffer_object);
			glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object);

			GLuint attach_target = 0;

			for (const auto& attachment : m_attachments)
			{
				const auto texture_object = attachment.second->ToTextureBufferObject()->GetTextureObject();
				//glBindTexture(GL_TEXTURE_2D, texture_object);

				switch (attachment.first)
				{
				case Scene::ELFAT_COLOR_ATTACHMENT0:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_object, 0);
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT0);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT1:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, texture_object, 0);
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT1);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT2:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, texture_object, 0);
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT2);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT3:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, texture_object, 0);
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT3);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT4:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, texture_object, 0);
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT4);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT5:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, texture_object, 0);
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT5);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT6:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, GL_TEXTURE_2D, texture_object, 0);
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT6);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT7:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT7, GL_TEXTURE_2D, texture_object, 0);
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT7);
					break;
					/*
					 * TODO: Finish depth & stencil buffer object binding
					 */
				case Scene::ELFAT_DEPTH_ATTACHMENT0:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_object, 0);
					//m_attachment_enums.push_back(GL_DEPTH_ATTACHMENT);
					break;
				case Scene::ELFAT_STENCIL_ATTACHMENT0:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture_object, 0);
					//m_attachment_enums.push_back(GL_STENCIL_ATTACHMENT);
					break;
				}
			}

			const bool completed = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
			if (!completed)
			{
				const auto error = glGetError();
				const auto error_string = glewGetErrorString(error);
				LogLine("[ERROR] Init frame buffer object error:" << error << " info:" << error_string);
				LEV_ASSERT(false);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			return true;
		}
	}
}

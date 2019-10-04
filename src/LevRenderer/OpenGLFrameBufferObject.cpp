#include "OpenGLFrameBufferObject.h"
#include "GlobalDef.h"
#include "LevFrameBufferObject.h"
#include "LevAttachment.h"
#include "OpenGLTextureBufferObject.h"
#include "OpenGLResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLFrameBufferObject::OpenGLFrameBufferObject(OpenGLObjectManager& object_manager, const Scene::LevFrameBufferObject& frame_buffer)
			: IOpenGLBufferObject(object_manager)
			, m_frame_buffer_object(0)
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
					m_attachments[attach_target_type].Reset(new OpenGLTextureBufferObject(m_object_manager, *texture));
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
			IOR_PUSH_ASYNC_RENDER_COMMAND(glDeleteFramebuffers(1, &m_frame_buffer_object));
		}

		OpenGLBufferBufferType OpenGLFrameBufferObject::GetBufferObjectType() const
		{
			return EOBBT_FRAME_BUFFER_OBJECT;
		}

		void OpenGLFrameBufferObject::Apply()
		{
			IOR_PUSH_ASYNC_RENDER_COMMAND(glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object));
			if (m_attachment_enums.empty())
			{
				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);
			}
			else
			{
				IOR_PUSH_ASYNC_RENDER_COMMAND(glDrawBuffers(m_attachment_enums.size(), &m_attachment_enums[0]));
			}

			/*
			 * TODO: Provide interface for user to set default clear operation
			 */
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OpenGLFrameBufferObject::UnApply()
		{
			IOR_PUSH_ASYNC_RENDER_COMMAND(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}

		bool OpenGLFrameBufferObject::_init_frame_object()
		{
			IOR_PUSH_ASYNC_RENDER_COMMAND(glGenFramebuffers(1, &m_frame_buffer_object));
			IOR_PUSH_ASYNC_RENDER_COMMAND(glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object));

			GLuint attach_target = 0;

			for (const auto& attachment : m_attachments)
			{
				const auto texture_object = attachment.second->ToTextureBufferObject()->GetTextureObject();
				//glBindTexture(GL_TEXTURE_2D, texture_object);

				switch (attachment.first)
				{
				case Scene::ELFAT_COLOR_ATTACHMENT0:
					IOR_PUSH_ASYNC_RENDER_COMMAND(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_object, 0));
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT0);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT1:
					IOR_PUSH_ASYNC_RENDER_COMMAND(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, texture_object, 0));
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT1);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT2:
					IOR_PUSH_ASYNC_RENDER_COMMAND(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, texture_object, 0));
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT2);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT3:
					IOR_PUSH_ASYNC_RENDER_COMMAND(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, texture_object, 0));
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT3);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT4:
					IOR_PUSH_ASYNC_RENDER_COMMAND(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, texture_object, 0));
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT4);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT5:
					IOR_PUSH_ASYNC_RENDER_COMMAND(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, texture_object, 0));
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT5);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT6:
					IOR_PUSH_ASYNC_RENDER_COMMAND(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, GL_TEXTURE_2D, texture_object, 0));
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT6);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT7:
					IOR_PUSH_ASYNC_RENDER_COMMAND(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT7, GL_TEXTURE_2D, texture_object, 0));
					m_attachment_enums.push_back(GL_COLOR_ATTACHMENT7);
					break;
					/*
					 * TODO: Finish depth & stencil buffer object binding
					 */
				case Scene::ELFAT_DEPTH_ATTACHMENT0:
					IOR_PUSH_ASYNC_RENDER_COMMAND(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_object, 0));
					//m_attachment_enums.push_back(GL_DEPTH_ATTACHMENT);
					break;
				case Scene::ELFAT_STENCIL_ATTACHMENT0:
					IOR_PUSH_ASYNC_RENDER_COMMAND(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture_object, 0));
					//m_attachment_enums.push_back(GL_STENCIL_ATTACHMENT);
					break;
				}
			}

			bool completed = false;
			IOR_PUSH_SYNC_RENDER_COMMAND(completed = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

			if (!completed)
			{
				const auto error = glGetError();
				const auto error_string = glewGetErrorString(error);
				LogLine("[ERROR] Init frame buffer object error:" << error << " info:" << error_string);
				LEV_ASSERT(false);
			}

			IOR_PUSH_ASYNC_RENDER_COMMAND(glBindFramebuffer(GL_FRAMEBUFFER, 0));

			return true;
		}
	}
}

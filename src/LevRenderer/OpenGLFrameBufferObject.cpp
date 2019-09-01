﻿#include "OpenGLFrameBufferObject.h"
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
					LPtr<Scene::LevTextureObject> texture = attachment.second->ToLevTextureObject();
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
			glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object);
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
				switch (attachment.first)
				{
				case Scene::ELFAT_COLOR_ATTACHMENT0:
					glFramebufferTexture2D(m_frame_buffer_object, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, attachment.second->ToTextureBufferObject()->GetTextureObject(), 0);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT1:
					glFramebufferTexture2D(m_frame_buffer_object, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, attachment.second->ToTextureBufferObject()->GetTextureObject(), 0);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT2:
					glFramebufferTexture2D(m_frame_buffer_object, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, attachment.second->ToTextureBufferObject()->GetTextureObject(), 0);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT3:
					glFramebufferTexture2D(m_frame_buffer_object, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, attachment.second->ToTextureBufferObject()->GetTextureObject(), 0);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT4:
					glFramebufferTexture2D(m_frame_buffer_object, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, attachment.second->ToTextureBufferObject()->GetTextureObject(), 0);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT5:
					glFramebufferTexture2D(m_frame_buffer_object, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, attachment.second->ToTextureBufferObject()->GetTextureObject(), 0);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT6:
					glFramebufferTexture2D(m_frame_buffer_object, GL_COLOR_ATTACHMENT6, GL_TEXTURE_2D, attachment.second->ToTextureBufferObject()->GetTextureObject(), 0);
					break;
				case Scene::ELFAT_COLOR_ATTACHMENT7:
					glFramebufferTexture2D(m_frame_buffer_object, GL_COLOR_ATTACHMENT7, GL_TEXTURE_2D, attachment.second->ToTextureBufferObject()->GetTextureObject(), 0);
					break;
					/*
					 * TODO: Finish depth & stencil buffer object binding
					 */
				case Scene::ELFAT_DEPTH_ATTACHMENT0:
					break;
				case Scene::ELFAT_STENCIL_ATTACHMENT0:
					break;
				}
			}

			LEV_ASSERT(glCheckFramebufferStatus(m_frame_buffer_object) == GL_FRAMEBUFFER_COMPLETE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			return true;
		}
	}
}

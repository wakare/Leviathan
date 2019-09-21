#pragma once
#include "IOpenGLObject.h"
#include "GL/glew.h"

namespace Leviathan
{
	namespace Renderer
	{
		enum OpenGLTextureObjectType
		{
			EOTOT_2D_TEX = GL_TEXTURE_2D,
			EOTOT_3D_TEX = GL_TEXTURE_3D,
		};

		class OpenGLColorTexture2DObject;
		class OpenGLDepthTexture2DObject;
		class OpenGLColorTexture3DObject;

		class IOpenGLTextureObject : public IOpenGLObject
		{
		public:
			IOpenGLTextureObject(OpenGLObjectManager& manager, GLuint texture_object_uid) 
				: IOpenGLObject(manager), m_texture_unit(0), m_texture_object(-1), m_texture_object_uid(texture_object_uid)
			{
				
			}

			virtual ~IOpenGLTextureObject() = default;

			void SetTextureUnitOffset(GLuint unit_offset) { m_texture_unit = unit_offset; };
			GLuint GetTextureUnitOffset() const { return m_texture_unit; };
			GLuint GetTextureObject() const { return m_texture_object; };

			virtual OpenGLTextureObjectType GetTextureObjectType() const = 0;
			IOpenGLTextureObject* ToOpenGLTextureObject() override { return this; };

			GLuint GetTextureObjectUID() const;

			void ActiveAndBind();
			void UnActiveAndUnBind();

			virtual OpenGLColorTexture2DObject* To2DColorTextureObject() { return nullptr; }
			virtual OpenGLDepthTexture2DObject* To2DDepthTextureObject() { return nullptr; }
			virtual OpenGLColorTexture3DObject* To3DColorTextureObject() { return nullptr; }

		protected:
			GLint m_texture_unit;
			GLuint m_texture_object;
			GLuint m_texture_object_uid;
		};

		inline GLuint IOpenGLTextureObject::GetTextureObjectUID() const
		{
			return m_texture_object_uid;
		}

		inline void IOpenGLTextureObject::ActiveAndBind()
		{
			glActiveTexture(GL_TEXTURE0 + m_texture_unit);
			glBindTexture(GetTextureObjectType(), m_texture_object);
		}

		inline void IOpenGLTextureObject::UnActiveAndUnBind()
		{
			glActiveTexture(GL_TEXTURE0 + m_texture_unit);
			glBindTexture(GetTextureObjectType(), 0);
		}
	}
}

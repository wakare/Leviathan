#pragma once
#include "IOpenGLObject.h"
#include "GL/glew.h"

namespace Leviathan
{
	namespace Renderer
	{
		enum OpenGLTextureObjectType
		{
			EOTOT_2D = GL_TEXTURE_2D,
			EOTOT_3D = GL_TEXTURE_3D
		};

		class OpenGLTexture2DObject;
		class OpenGLTexture3DObject;

		class IOpenGLTextureObject : public IOpenGLObject
		{
		public:
			IOpenGLTextureObject(OpenGLObjectManager& manager) : IOpenGLObject(manager), m_texture_unit(-1), m_texture_object(-1) {}
			virtual ~IOpenGLTextureObject() = default;

			void SetTextureUnitOffset(GLuint unit_offset) { m_texture_unit = unit_offset; };
			GLuint GetTextureUnitOffset() const { return m_texture_unit; };
			GLuint GetTextureObject() const { return m_texture_object; };

			virtual OpenGLTextureObjectType GetTextureObjectType() const = 0;
			IOpenGLTextureObject* ToOpenGLTextureObject() override { return this; };

			void ActiveAndBind() 
			{
				glActiveTexture(GL_TEXTURE0 + m_texture_unit);
				glBindTexture(GetTextureObjectType(), m_texture_object);
			};

			void UnActiveAndUnBind()
			{
				glActiveTexture(GL_TEXTURE0 + m_texture_unit);
				glBindTexture(GetTextureObjectType(), 0);
			};

			virtual OpenGLTexture2DObject* To2DTextureObject() { return nullptr; }
			virtual OpenGLTexture3DObject* To3DTextureObject() { return nullptr; }

		protected:
			GLint m_texture_unit;
			GLuint m_texture_object;
		};
	}
}

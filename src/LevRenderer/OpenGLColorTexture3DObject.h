#pragma once

#include "IOpenGLTextureObject.h"
#include "GL/glew.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLColorTexture3DObject : public IOpenGLTextureObject
		{
		public:
			~OpenGLColorTexture3DObject();

			OpenGLTextureObjectType GetTextureObjectType() const override { return EOTOT_3D_TEX; };
			OpenGLColorTexture3DObject* To3DColorTextureObject() override { return this; }

		protected:
			friend class OpenGLObjectManager;
			/*
			 * OpenGL Object resource should be created in Object manager class
			 */
			OpenGLColorTexture3DObject(OpenGLObjectManager& manager, GLuint texture_object_uid, GLuint width, GLuint height, GLuint depth, const GLvoid* data);

			GLuint m_width;
			GLuint m_height;
			GLuint m_depth;
		};
	}
}



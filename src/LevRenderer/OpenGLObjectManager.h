#pragma once

#include "LSPtr.h"
#include <gl/glew.h>
#include <map>
#include "LevTextureObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLTextureObject;

		class OpenGLObjectManager
		{
		public:
			OpenGLObjectManager();

			/*
			 ***************************************** Resource generation
			 * Every object resource should be generated by Object Manager.
			 */
			bool CreateTextureResource(Scene::LevTextureType tex_type, GLuint texture_object_uid, GLuint width, GLuint height, GLuint depth, const GLvoid* data, LSPtr<IOpenGLTextureObject>& out);

			bool GetTextureResource(GLuint texture_object_uid, LSPtr<IOpenGLTextureObject>& out);

		private:
			std::map<GLuint, LSPtr<IOpenGLTextureObject>> m_texture_objects;
		};
	}
}

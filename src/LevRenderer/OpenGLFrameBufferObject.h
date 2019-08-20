#pragma once
#include <GL/glew.h>

namespace Leviathan
{
	namespace Scene
	{
		class LevFrameBufferObject;
	}

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
			GLuint m_frame_buffer_object;
			const Scene::LevFrameBufferObject& m_frame_buffer;
		};
	}
}


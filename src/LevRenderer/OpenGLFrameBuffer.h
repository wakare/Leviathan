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
		class OpenGLFrameBuffer
		{
		public:
			OpenGLFrameBuffer(const Scene::LevFrameBufferObject& frame_buffer);
			~OpenGLFrameBuffer();

			void Apply();
			void UnApply();

		private:

			GLuint m_frame_buffer_object;
			const Scene::LevFrameBufferObject& m_frame_buffer;
		};
	}
}


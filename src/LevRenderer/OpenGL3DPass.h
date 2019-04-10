#pragma once
#include "OpenGLPass.h"
#include "LevCamera.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGL3DPass : public OpenGLPass
		{
		public:
			OpenGL3DPass(LPtr<OpenGLShaderProgram> shaderProgram, const Scene::LevCamera* camera);
			~OpenGL3DPass();

			bool Init();
			void Render();
			void SetCullFace(GLenum cullmode = GL_CCW);
			void SetCullFaceEnable(GLboolean bEnable);

		private:
			void _updateCameraMatrixUniform(GLuint shaderProgram);
			GLboolean _updateLightEnableUniform(GLuint shaderProgram, GLboolean bLightEnable);

			bool m_bInited;
			const Scene::LevCamera* m_pMainCamera;

			GLboolean m_bFaceCullEnable;
			GLenum m_faceCullMode;
		};
	}
}
#pragma once

#include "GLPass.h"
#include "Camera.h"
#include "LPtr.h"
#include "GLCommonMaterial.h"

namespace Leviathan
{
	class TriDObjectGLPass : public GLPass
	{
	public:
		TriDObjectGLPass(LPtr<GLShaderProgram> shaderProgram, LPtr<Camera> camera);
		~TriDObjectGLPass();

		bool Init();
		void Render();
		void SetCullFace(GLenum cullmode = GL_CCW);
		void SetCullFaceEnable(GLboolean bEnable);

	private:
		void _updateCameraMatrixUniform(GLuint shaderProgram);
		GLboolean _updateLightEnableUniform(GLuint shaderProgram, GLboolean bLightEnable);

		bool m_bInited;
		LPtr<Camera> m_pMainCamera;

		GLboolean m_bFaceCullEnable;
		GLenum m_faceCullMode;
	};
}
#pragma once
#include "GLPass.h"
#include "GLCamera.h"
#include "LPtr.h"
#include "CommonGLMaterial.h"

namespace Leviathan
{
	class TriDObjectGLPass : public GLPass
	{
	public:
		TriDObjectGLPass(LPtr<GLShaderProgram> shaderProgram, LPtr<GLCamera> camera) :
			GLPass(shaderProgram),
			m_bInited(false),
			m_pMainCamera(camera)
		{
		};

		bool Init();
		void Render();

	private:
		void _updateCameraMatrixUniform(GLuint shaderProgram);
		GLboolean _updateLightEnableUniform(GLuint shaderProgram, GLboolean bLightEnable);

		bool m_bInited;
		LPtr<GLCamera> m_pMainCamera;
	};
}
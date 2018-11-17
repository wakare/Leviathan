#pragma once
#include "GLPass.h"
#include "GLCamera.h"
#include "LPtr.h"
namespace Leviathan
{
	class TriDObjectGLPass : public GLPass
	{
	public:
		TriDObjectGLPass(LPtr<GLShaderProgram> shaderProgram, LPtr<GLCamera> camera) :
			GLPass(shaderProgram),
			m_bInited(false),
			m_mainCamera(camera)
		{
		};

		virtual bool Init();
		virtual void Render();

	private:
		void _updateCameraMatrixUniform(GLuint shaderProgram);

		bool m_bInited;
		LPtr<GLCamera> m_mainCamera;
	};
}
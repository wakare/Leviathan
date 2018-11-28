#pragma once
#include "GLPass.h"
#include "GLCamera.h"
#include "LPtr.h"
#include "GLCommonMaterial.h"

namespace Leviathan
{
	class TriDObjectGLPass : public GLPass
	{
	public:
		TriDObjectGLPass(LPtr<GLShaderProgram> shaderProgram, LPtr<GLCamera> camera) :
			GLPass(shaderProgram),
			m_bInited(false),
			m_pMainCamera(camera),
			m_bFaceCullEnable(false),
			m_faceCullMode(GL_CCW)
		{
		};

		~TriDObjectGLPass() 
		{
		};

		bool Init();
		void Render();
		void SetCullFace(GLenum cullmode = GL_CCW);
		void SetCullFaceEnable(GLboolean bEnable);

	private:
		void _updateCameraMatrixUniform(GLuint shaderProgram);
		GLboolean _updateLightEnableUniform(GLuint shaderProgram, GLboolean bLightEnable);

		bool m_bInited;
		LPtr<GLCamera> m_pMainCamera;

		GLboolean m_bFaceCullEnable;
		GLenum m_faceCullMode;
	};
}
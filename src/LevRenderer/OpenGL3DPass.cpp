#include "OpenGL3DPass.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLUniform.h"
#include "OpenGLObject.h"
#include "OpenGLPointLight.h"
#include "OpenGLMaterial.h"
#include "OpenGL3DObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGL3DPass::OpenGL3DPass(LPtr<OpenGLShaderProgram> shaderProgram, const Scene::LevCamera* camera) :
			OpenGLPass(shaderProgram),
			m_bInited(false),
			m_pMainCamera(camera),
			m_bFaceCullEnable(false),
			m_faceCullMode(GL_CCW)
		{
		};

		OpenGL3DPass::~OpenGL3DPass()
		{
		};

		bool OpenGL3DPass::Init()
		{
			if (m_bInited || !m_pGLShaderProgram) return true;

			EXIT_IF_FALSE(m_pGLShaderProgram->Init());

			LPtr<OpenGLUniform> viewMatrixUniform = new OpenGLUniform("viewMatrix", OpenGLUniform::TYPE_FLOAT_MAT4);
			auto viewMatrix = m_pMainCamera->GetViewportMatrix();
			viewMatrixUniform->SetData(viewMatrix.data(), viewMatrix.size());
			if (!m_pGLShaderProgram->AddUniform(viewMatrixUniform))
			{
				throw "TriDObjectGLPass::Init() failed.";
				return false;
			}

			LPtr<OpenGLUniform> PerspectiveMatrixUniform = new OpenGLUniform("projMatrix", OpenGLUniform::TYPE_FLOAT_MAT4);
			auto projMatrix = m_pMainCamera->GetProjectMatrix();
			PerspectiveMatrixUniform->SetData(projMatrix.data(), projMatrix.size());
			if (!m_pGLShaderProgram->AddUniform(PerspectiveMatrixUniform))
			{
				throw "TriDObjectGLPass::Init() failed.";
				return false;
			}

			m_bInited = true;
			return true;
		}

		void OpenGL3DPass::Render()
		{
			// Call PreCallBack
			for (auto& process : m_PreRenderCallBacks)
			{
				process();
			}

			// Set face cull mode
			if (m_bFaceCullEnable)
			{
				glCullFace(m_faceCullMode);
			}

			// Set renderType
			(m_bDepthTestEnable) ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

			glPolygonMode(GL_FRONT_AND_BACK, m_nPolygonMode);

			// Set GLProgram
			auto program = m_pGLShaderProgram->GetShaderProgram();
			glUseProgram(program);
			//m_pGLShaderProgram->SetGLUniformState();

			// Set light
			if (m_bLightEnable)
			{
				for (auto& pLight : m_lights)
				{
					if (!pLight->SetLightUniformVar(program))
					{
						LogLine("[ERROR] Set light uniform var failed.");
					}
				}
			}

			// Set viewMatrix
			// _updateCameraMatrixUniform(program);

			// Apply uniforms
			_applyUniforms();

			// Render each GLObject
			for (auto& pObject : m_GLObjects)
			{
				OpenGL3DObject* p3dObject = dynamic_cast<OpenGL3DObject*>(pObject.Get());
				if (!p3dObject)
				{
					continue;
				}

				auto lightEnable = m_bLightEnable && pObject->HasMaterial() && pObject->ApplyMaterial(program);
				p3dObject->SetLightEnable(lightEnable);

				m_pGLShaderProgram->SetGLUniformState();
				pObject->Update();
				pObject->Render(program);
			}

			// ResetProgram
			glUseProgram(0);
			glDisable(GL_DEPTH_TEST);

			// Call PostCallBack
			for (auto& process : m_PostRenderCallBacks)
			{
				process();
			}
		}

		void OpenGL3DPass::SetCullFace(GLenum cullmode /*= GL_CCW*/)
		{
			SetCullFaceEnable(true);
			m_faceCullMode = cullmode;
		}

		void OpenGL3DPass::SetCullFaceEnable(GLboolean bEnable)
		{
			m_bFaceCullEnable = bEnable;
			if (m_bFaceCullEnable) glEnable(GL_CULL_FACE);
			else glDisable(GL_CULL_FACE);
		}

		void OpenGL3DPass::_updateCameraMatrixUniform(GLuint shaderProgram)
		{
			auto& pViewMatrixUniform = m_pGLShaderProgram->GetUniformByName("viewMatrix");
			if (!pViewMatrixUniform)
			{
				throw "TriDObjectGLPass::_updateCameraMatrixUniform(GLuint shaderProgram) --> GetUniform failed.";
				return;
			}

			auto viewMatrix = m_pMainCamera->GetViewportMatrix();
			pViewMatrixUniform->SetData(viewMatrix.data(), viewMatrix.size());

			auto& pPerspectiveMatrixUniform = m_pGLShaderProgram->GetUniformByName("projMatrix");
			if (!pPerspectiveMatrixUniform)
			{
				throw "TriDObjectGLPass::_updateCameraMatrixUniform(GLuint shaderProgram) --> GetUniform failed.";
				return;
			}

			auto PerspectiveMatrix = m_pMainCamera->GetProjectMatrix();
			pPerspectiveMatrixUniform->SetData(PerspectiveMatrix.data(), PerspectiveMatrix.size());

			int viewPosLocation = glGetUniformLocation(shaderProgram, "viewPos");
			if (viewPosLocation == -1)
			{
				LeviathanOutStream << "[ERROR] Get viewPos uniform failed." << std::endl;
				return;
			}

			auto& eyePos = m_pMainCamera->GetEyePos();
			glUniform3f(viewPosLocation, eyePos[0], eyePos[1], eyePos[2]);
		}

		GLboolean OpenGL3DPass::_updateLightEnableUniform(GLuint shaderProgram, GLboolean bLightEnable)
		{
			GLint nLightEnableUniformLocation = glGetUniformLocation(shaderProgram, "bLightOpen");
			if (nLightEnableUniformLocation == -1)
			{
				LeviathanOutStream << "[ERROR] Get lightOpen uniform failed." << std::endl;
				return false;
			}

			glUniform1i(nLightEnableUniformLocation, bLightEnable);
			return true;
		}
	}
}
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

			// Apply uniforms
			_applyUniforms();

			// Render each GLObject
			for (auto& pObjectSet : m_GLObjectMap)
			{
				for (auto& pObject : pObjectSet.second)
				{
					if (!pObject->GetVisible())
					{
						continue;
					}

					pObject->PreProcess();

					OpenGL3DObject* p3dObject = dynamic_cast<OpenGL3DObject*>(pObject.Get());
					if (p3dObject)
					{
						auto lightEnable = m_bLightEnable && pObject->HasMaterial() && pObject->ApplyMaterial(program);
						p3dObject->SetLightEnable(lightEnable);
					}

					m_pGLShaderProgram->SetGLUniformState();
					pObject->Update();
					pObject->Render(program);

					pObject->PostProcess();
				}
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
	}
}
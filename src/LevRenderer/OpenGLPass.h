#pragma once

#include <functional>
#include <vector>
#include <gl/glew.h>
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLShaderProgram;
		class OpenGLObject;
		class OpenGLLight;
		class OpenGLUniform;

		class OpenGLPass
		{
		public:
			typedef std::function<void(void)> Process;
			OpenGLPass(LPtr<OpenGLShaderProgram> shaderProgram);
			virtual ~OpenGLPass();

			void AddGLObject(LPtr<OpenGLObject> pObject);
			void AddGLObject(std::vector<LPtr<OpenGLObject>>& pGLObjectVec);
			void RemoveGLObject(LPtr<OpenGLObject> pObject);
			void ClearGLObject();
			void AddGLLight(LPtr<OpenGLLight> pLight);
			const std::vector<LPtr<OpenGLObject>> GetGLObjects();

			virtual bool Init() = 0;
			virtual void Render() = 0;

			void AddPreProcess(Process process);
			void AddPostProcess(Process process);
			void SetPolygonMode(GLuint nPolygonMode);
			void SetLightEnable(GLboolean bOpen);
			void SetDepthTestEnable(GLboolean bDepthTestEnable);

			void AddUniform(LPtr<OpenGLUniform> pUniform);
			void RemoveUniform(LPtr<OpenGLUniform> pUniform);

		protected:
			void _applyUniforms();
			std::vector<LPtr<OpenGLObject>>::iterator _findGLObject(LPtr<OpenGLObject>& pObject);

			LPtr<OpenGLShaderProgram> m_pGLShaderProgram;
			std::vector<LPtr<OpenGLUniform>> m_pUniforms;
			std::vector<LPtr<OpenGLObject>> m_GLObjects;
			std::vector<LPtr<OpenGLLight>> m_lights;

			std::vector<Process> m_PreRenderCallBacks;
			std::vector<Process> m_PostRenderCallBacks;

			GLuint m_nPolygonMode;
			GLboolean m_bLightEnable;
			GLboolean m_bDepthTestEnable;
		};
	}
}
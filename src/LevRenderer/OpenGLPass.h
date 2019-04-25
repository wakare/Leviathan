#pragma once

#include <functional>
#include <vector>
#include <map>
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
			void AddGLObject(unsigned id, const std::vector<LPtr<OpenGLObject>>& pGLObjectVec);
			bool ReplaceGLObject(unsigned id, const std::vector<LPtr<OpenGLObject>>& objects);
			void RemoveGLObject(unsigned id);
			void ClearGLObject();
			void AddGLLight(LPtr<OpenGLLight> pLight);

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
			bool _findGLObject(unsigned id, std::vector<LPtr<OpenGLObject>>& out_pObject);

			LPtr<OpenGLShaderProgram> m_pGLShaderProgram;
			std::vector<LPtr<OpenGLUniform>> m_pUniforms;
			std::map<unsigned, std::vector<LPtr<OpenGLObject>>> m_GLObjectMap;
			std::vector<LPtr<OpenGLLight>> m_lights;

			std::vector<Process> m_PreRenderCallBacks;
			std::vector<Process> m_PostRenderCallBacks;

			GLuint m_nPolygonMode;
			GLboolean m_bLightEnable;
			GLboolean m_bDepthTestEnable;
		};
	}
}
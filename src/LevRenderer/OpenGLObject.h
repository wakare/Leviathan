#pragma once

#include <vector>
#include <gl/glew.h>
#include <Eigen/Dense>
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLMaterial;
		class OpenGLUniform;
		class OpenGLShaderProgram;

		class OpenGLObject
		{
		public:
			enum VertexAttributeType
			{
				VERTEX_ATTRIBUTE_XYZ = 0x1,		// Coord XYZ
				VERTEX_ATTRIBUTE_RGBA = 0x2,	// Color RGBAs
				VERTEX_ATTRIBUTE_NXYZ = 0x4,	// Normal XYZ
				VERTEX_ATTRIBUTE_TEX = 0x8,
			};

			OpenGLObject(unsigned id, GLuint primType, GLuint vertexCount, GLint vertexMask, LPtr<OpenGLMaterial> pMaterial = nullptr);

			virtual ~OpenGLObject();

			unsigned GetID() const;
			GLuint GetVAO();
			GLuint GetVBO();
			GLuint GetIBO();
			GLuint GetPrimType();
			GLuint GetVertexCount();
			GLuint GetVertexMask();

			void SetVisible(bool visible);
			bool GetVisible() const;

			void SetMaterial(LPtr<OpenGLMaterial> pMaterial);
			bool ApplyMaterial(GLuint shaderProgram);

			GLboolean HasMaterial() const;

			void AddUniform(LPtr<OpenGLUniform> pUniform);
			void RemoveUniform(LPtr<OpenGLUniform> pUniform);
			bool ApplyUniform(GLuint shaderProgram);

			void SetShaderProgram(LPtr<OpenGLShaderProgram> shader_program);
			const LPtr<OpenGLShaderProgram> GetShaderProgram() const;

			void AddPreProcess(std::function<void()> fn);
			void AddPostProcess(std::function<void()> fn);

			bool PreProcess();
			bool PostProcess();

			virtual bool Init() = 0;
			virtual bool Update() = 0;
			virtual bool Render(GLuint shaderProgram) = 0;

		protected: 
			const unsigned m_ID;
			GLuint m_VAO;
			GLuint m_VBO;
			GLuint m_IBO;
			GLuint m_primitiveType;
			GLuint m_vertexCount;
			GLint m_vertexAttributeMask;

			bool m_visible;

			LPtr<OpenGLMaterial> m_pMaterial;
			LPtr<OpenGLShaderProgram> m_shader_program;
			std::vector<LPtr<OpenGLUniform>> m_pUniforms;

			std::vector<std::function<void()>> m_preprocess_fns;
			std::vector<std::function<void()>> m_postprocess_fns;
		};
	}
}

#pragma once

#include <map>
#include <gl/glew.h>
#include <Eigen/Dense>
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLMaterial;
		class OpenGLUniform;

		class OpenGLObject
		{
		public:
			enum VertexAttributeType
			{
				VERTEX_ATTRIBUTE_XYZ = 0x1,	// Coord XYZ
				VERTEX_ATTRIBUTE_RGBA = 0x2,	// Color RGBAs
				VERTEX_ATTRIBUTE_NXYZ = 0x4,	// Normal XYZ
				VERTEX_ATTRIBUTE_TEX = 0x8,
			};

			OpenGLObject(GLuint primType, GLuint vertexCount, GLint vertexMask, LPtr<Eigen::Matrix4f> pModelMatrix = nullptr, LPtr<OpenGLMaterial> pCommonGLMaterial = nullptr);

			virtual ~OpenGLObject();

			GLuint GetVAO();
			GLuint GetVBO();
			GLuint GetIBO();
			GLuint GetPrimType();
			GLuint GetVertexCount();
			GLuint GetVertexMask();
			GLboolean GetLightEnable();

			void SetModelMatrix(const Eigen::Matrix4f& refModelMatrix);

			void SetMaterial(LPtr<OpenGLMaterial> pMaterial);
			void SetLightEnable(bool bLightEnable);
			void SetDefaultVertexColorEnable(bool bUseDefaultVertexColor);
			GLboolean HasMaterial() const;

			void AddUniform(LPtr<OpenGLUniform> pUniform);

			virtual bool Init() = 0;
			virtual bool ApplyMaterial(GLuint shaderProgram) = 0;
			virtual bool ApplyModelMatrix(LPtr<OpenGLUniform>& modelUniform) = 0;
			virtual bool ApplyUniform(GLuint shaderProgram) = 0;
			virtual bool Render(GLuint shaderProgram) = 0;

		protected:
			GLboolean m_bLightEnable;
			GLboolean m_bUseDefaultVertexColor;

			GLuint m_VAO;
			GLuint m_VBO;
			GLuint m_IBO;
			GLuint m_primitiveType;
			GLuint m_vertexCount;
			GLint m_vertexAttributeMask;
			LPtr<OpenGLMaterial> m_pCommonGLMaterial;
			LPtr<Eigen::Matrix4f> m_pModelMatrix;
			std::map<std::string, LPtr<OpenGLUniform>> m_pUniforms;
		};
	}
}

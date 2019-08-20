#include "OpenGLTextureUniform.h"
#include "LevTextureObject.h"
#include "LevTextureUniform.h"
#include "OpenGLTexture2DObject.h"
#include "OpenGLTexture3DObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLTextureUniform::OpenGLTextureUniform(const Scene::LevTextureUniform& texture)
			: m_texture_uniform_name(texture.GetName())
			, m_texture_uniform_location(-1)
		{
			const auto& texture_object = texture.GetUniformData();

			switch(texture_object.GetTextureType())
			{
				case Scene::ELTT_2D_TEXTURE:
					m_texture_object.Reset(new OpenGLTexture2DObject(texture_object.GetWidth(), texture_object.GetHeight(), texture_object.GetTextureData()));
					break;

				case Scene::ELTT_3D_TEXTURE:
					m_texture_object.Reset(new OpenGLTexture3DObject(texture_object.GetWidth(), texture_object.GetHeight(), texture_object.GetDepth(), texture_object.GetTextureData()));
					break;

				default:
					LEV_ASSERT(false);
			}

			m_texture_object->SetTextureUnitOffset(0);
		}

		OpenGLTextureUniform::~OpenGLTextureUniform()
		= default;

		const std::string& OpenGLTextureUniform::GetUniformName() const
		{
			return m_texture_uniform_name;
		};

		bool OpenGLTextureUniform::Apply(GLuint shaderProgram)
		{
			m_texture_object->ActiveAndBind();

			if (m_texture_uniform_location == -1)
			{
				m_texture_uniform_location = glGetUniformLocation(shaderProgram, m_texture_uniform_name.c_str());
				LEV_ASSERT(m_texture_uniform_location != -1);
			}

			glUniform1i(m_texture_uniform_location, GL_TEXTURE0 + m_texture_object->GetTextureUnitOffset());
			return true;
		}

		bool OpenGLTextureUniform::UnApply(GLuint shaderProgram)
		{
			m_texture_object->UnActiveAndUnBind();
			return true;
		}

	}
}
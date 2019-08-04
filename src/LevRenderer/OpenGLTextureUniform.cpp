#include "OpenGLTextureUniform.h"
#include "LevTextureObject.h"
#include "OpenGLTexture2DObject.h"
#include "OpenGLTexture3DObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLTextureUniform::OpenGLTextureUniform(const Scene::LevTextureObject& texture) 
			: m_texture_uniform_name(texture.GetTextureUniformName())
			, m_texture_uniform_location(-1)
		{
			switch(texture.GetTextureType())
			{
				case Scene::ELTT_2D_TEXTURE:
					m_texture_object.Reset(new OpenGLTexture2DObject(texture.GetWidth(), texture.GetHeight(), texture.GetTextureData()));
					break;

				case Scene::ELTT_3D_TEXTURE:
					m_texture_object.Reset(new OpenGLTexture3DObject(texture.GetWidth(), texture.GetHeight(), texture.GetDepth(), texture.GetTextureData()));
					break;

				default:
					LEV_ASSERT(false);
			}
			
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
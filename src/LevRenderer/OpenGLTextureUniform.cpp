#include "OpenGLTextureUniform.h"
#include "LevTextureObject.h"
#include "OpenGLTextureObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLTextureUniform::OpenGLTextureUniform(const Scene::LevTextureObject& texture) 
			: m_texture_uniform_name(texture.GetTextureUniformName())
			, m_texture_uniform_location(-1)
		{
			m_texture_object.Reset(new OpenGLTextureObject(texture.GetWidth(), texture.GetHeight(), texture.GetTextureData()));
		}

		OpenGLTextureUniform::~OpenGLTextureUniform()
		= default;

		const std::string& OpenGLTextureUniform::GetUniformName() const
		{
			return m_texture_uniform_name;
		};

		bool OpenGLTextureUniform::Apply(GLuint shaderProgram)
		{
			glActiveTexture(GL_TEXTURE0 + m_texture_object->GetTextureUnitOffset());
			glBindTexture(GL_TEXTURE_2D, m_texture_object->GetTextureObject());

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
			glActiveTexture(GL_TEXTURE0 + m_texture_object->GetTextureUnitOffset());
			glBindTexture(GL_TEXTURE_2D, 0);

			return true;
		}

	}
}
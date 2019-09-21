#include "OpenGLTextureUniform.h"
#include "LevTextureObject.h"
#include "LevTextureUniform.h"
#include "OpenGLColorTexture2DObject.h"
#include "OpenGLColorTexture3DObject.h"
#include "OpenGLResourceManager.h"
#include "OpenGLObjectManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLTextureUniform::OpenGLTextureUniform(const Scene::LevTextureUniform& texture)
			: m_texture_uniform_name(texture.GetName())
			, m_texture_uniform_location(-1)
		{
			const auto& texture_object = texture.GetUniformData();

			auto& object_manager = OpenGLResourceManager::Instance().GetObjectManager();

			if (!object_manager.GetTextureResource(texture_object.GetID(), m_texture_object))
			{
				const bool created = object_manager.CreateTextureResource(texture_object.GetTextureType(), texture_object.GetID(), texture_object.GetWidth(),
					texture_object.GetHeight(), texture_object.GetDepth(), texture_object.GetTextureData(), m_texture_object);
				LEV_ASSERT(created);
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

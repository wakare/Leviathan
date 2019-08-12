#include "LevRAttrTextureUniform.h"
#include "LevTokenDispatch.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrTextureUniform::LevRAttrTextureUniform(const std::string& name)
			: m_uniform_id(LevTokenDispatch<ILevRAttrUniform, unsigned>::GetIncrementToken())
			, m_uniform_name(name)
			, m_texture_object(nullptr)
		{
		}

		unsigned LevRAttrTextureUniform::GetId() const
		{
			return m_uniform_id;
		}

		void LevRAttrTextureUniform::SetName(const std::string& name)
		{
			m_uniform_name = name;
		}

		const std::string& LevRAttrTextureUniform::GetName() const
		{
			return m_uniform_name;
		}

		LevUniformType LevRAttrTextureUniform::GetUniformType() const
		{
			return ELUT_TEXTURE;
		}

		void LevRAttrTextureUniform::SetUniformData(LPtr<LevTextureObject> texture_object)
		{
			m_texture_object = texture_object;
		}

		const LevTextureObject& LevRAttrTextureUniform::GetUniformData() const
		{
			return *m_texture_object;
		}
	}
}

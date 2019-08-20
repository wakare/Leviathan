#include "LevTextureUniform.h"
#include "LevTokenDispatch.h"

namespace Leviathan
{
	namespace Scene
	{
		LevTextureUniform::LevTextureUniform(const std::string& name)
			: m_uniform_id(LevTokenDispatch<ILevUniform, unsigned>::GetIncrementToken())
			, m_uniform_name(name)
			, m_texture_object(nullptr)
		{
		}

		unsigned LevTextureUniform::GetId() const
		{
			return m_uniform_id;
		}

		void LevTextureUniform::SetName(const std::string& name)
		{
			m_uniform_name = name;
		}

		const std::string& LevTextureUniform::GetName() const
		{
			return m_uniform_name;
		}

		LevUniformType LevTextureUniform::GetUniformType() const
		{
			return ELUT_TEXTURE;
		}

		void LevTextureUniform::SetUniformData(LPtr<LevTextureObject> texture_object)
		{
			m_texture_object = texture_object;
		}

		const LevTextureObject& LevTextureUniform::GetUniformData() const
		{
			return *m_texture_object;
		}
	}
}

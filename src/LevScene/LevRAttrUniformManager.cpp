#include "LevRAttrUniformManager.h"
#include "ILevUniform.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrUniformManager::LevRAttrUniformManager()
			: LevSceneObjectAttribute(ELSOAT_RENDER)
		{
		}

		void LevRAttrUniformManager::AddUniform(LSPtr<ILevUniform> uniform)
		{
			m_uniforms[uniform->GetName()] = uniform;
		}


		const std::map<std::string, Leviathan::LSPtr<Leviathan::Scene::ILevUniform>>& LevRAttrUniformManager::GetUniforms() const
		{
			return m_uniforms;
		}

	}
}
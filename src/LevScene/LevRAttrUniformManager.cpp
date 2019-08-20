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

		void LevRAttrUniformManager::AddUniform(LPtr<ILevUniform> uniform)
		{
			m_uniforms[uniform->GetName()] = uniform;
		}


		const std::map<std::string, Leviathan::LPtr<Leviathan::Scene::ILevUniform>>& LevRAttrUniformManager::GetUniforms() const
		{
			return m_uniforms;
		}

	}
}
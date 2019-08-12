#include "LevRAttrUniformManager.h"
#include "ILevRAttrUniform.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrUniformManager::LevRAttrUniformManager()
			: LevSceneObjectAttribute(ELSOAT_RENDER)
		{
		}

		void LevRAttrUniformManager::AddUniform(LPtr<ILevRAttrUniform> uniform)
		{
			m_uniforms[uniform->GetName()] = uniform;
		}


		const std::map<std::string, Leviathan::LPtr<Leviathan::Scene::ILevRAttrUniform>>& LevRAttrUniformManager::GetUniforms() const
		{
			return m_uniforms;
		}

	}
}
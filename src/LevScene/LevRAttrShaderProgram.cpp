#include "LevRAttrShaderProgram.h"
#include "LevTokenDispatch.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrShaderProgram::LevRAttrShaderProgram()
			: LevSceneObjectAttribute(ELSOAT_RENDER)
			, m_id(LevTokenDispatch<LevRAttrShaderProgram, unsigned>::GetIncrementToken())
		{

		}

		bool LevRAttrShaderProgram::SetShaderProgram(LSPtr<LevShaderProgram> program)
		{
			m_shader_program = program;

			return true;
		}

		unsigned LevRAttrShaderProgram::GetID() const
		{
			return m_id;
		}

		const Leviathan::Scene::LevShaderProgram& LevRAttrShaderProgram::GetShaderProgram() const
		{
			return *m_shader_program;
		}

	}
}
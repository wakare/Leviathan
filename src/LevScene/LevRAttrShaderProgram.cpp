#include "LevRAttrShaderProgram.h"
#include "LevTokenDispatch.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrShaderProgram::LevRAttrShaderProgram()
			: LevSceneObjectAttribute(ELSOAT_RENDER)
			, m_id(LevTokenDispatch<LevRAttrShaderProgram, unsigned>::GetToken())
		{

		}

		bool LevRAttrShaderProgram::SetShaderProgram(LPtr<LevShaderProgram> program)
		{
			m_shader_program = program;

			return true;
		}

		unsigned LevRAttrShaderProgram::GetID() const
		{
			return 0;
		}

		const Leviathan::Scene::LevShaderProgram& LevRAttrShaderProgram::GetShaderProgram() const
		{
			return *m_shader_program;
		}

	}
}
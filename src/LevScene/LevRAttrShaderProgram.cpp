#include "LevRAttrShaderProgram.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrShaderProgram::LevRAttrShaderProgram()
			: LevSceneObjectAttribute(ELSOAT_RENDER)
		{

		}

		bool LevRAttrShaderProgram::SetShaderProgram(LPtr<LevShaderProgram> program)
		{
			m_shader_program = program;

			return true;
		}

	}
}
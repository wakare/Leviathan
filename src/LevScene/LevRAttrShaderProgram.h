#pragma once

#include "LevSceneRenderAttribute.h"
#include "LPtr.h"
#include <string>

namespace Leviathan
{
	namespace Scene
	{
		struct LevShaderProgram
		{
			std::string m_vert_shader;
			std::string m_geom_shader;
			std::string m_frag_shader;
		};

		/*
			If node has it own shader program, all children will be applied this program.
		*/
		class LEV_SCENE_API LevRAttrShaderProgram : public LevSceneRenderAttribute
		{
		public:
			LevRAttrShaderProgram();
			bool SetShaderProgram(LPtr<LevShaderProgram> program);
			unsigned GetID() const;
			const LevShaderProgram& GetShaderProgram() const;

		private:
			LPtr<LevShaderProgram> m_shader_program;
			const unsigned m_id;
		};
	}
}
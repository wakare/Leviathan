#pragma once

#include "LevSceneRenderAttribute.h"
#include "LSPtr.h"
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

			ADD_RENDER_ATTRIBUTE_IMPLEMENT(LevRAttrShaderProgram);

			RenderAttributeType GetRenderAttributeType() const override { return ERAT_SHADER_PROGRAM; }

			bool SetShaderProgram(LSPtr<LevShaderProgram> program);
			unsigned GetID() const;
			const LevShaderProgram& GetShaderProgram() const;

		private:
			LSPtr<LevShaderProgram> m_shader_program;
			const unsigned m_id;
		};
	}
}
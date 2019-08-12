#pragma once
#include "ILevRAttrUniform.h"
#include "LevSceneAPIDefine.h"
#include <string>
#include "LPtr.h"
#include "LevTextureObject.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevRAttrTextureUniform : public ILevRAttrUniform
		{
		public:
			LevRAttrTextureUniform(const std::string& name);

			unsigned GetId() const override;
			void SetName(const std::string& name) override;
			const std::string& GetName() const override;
			LevUniformType GetUniformType() const override;

			void SetUniformData(LPtr<LevTextureObject> texture_object);
			const LevTextureObject& GetUniformData() const;

		private:
			const unsigned m_uniform_id;
			std::string m_uniform_name;
			LPtr<LevTextureObject> m_texture_object;
		};
	}
}

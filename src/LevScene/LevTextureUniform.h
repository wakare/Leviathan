#pragma once
#include "ILevUniform.h"
#include "LevSceneAPIDefine.h"
#include <string>
#include "LSPtr.h"
#include "LevTextureObject.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevTextureUniform : public ILevUniform
		{
		public:
			LevTextureUniform(const std::string& name);

			unsigned GetId() const override;
			void SetName(const std::string& name) override;
			const std::string& GetName() const override;
			LevUniformType GetUniformType() const override;

			void SetUniformData(LSPtr<LevTextureObject> texture_object);
			const LevTextureObject& GetUniformData() const;

		private:
			const unsigned m_uniform_id;
			std::string m_uniform_name;
			LSPtr<LevTextureObject> m_texture_object;
		};
	}
}

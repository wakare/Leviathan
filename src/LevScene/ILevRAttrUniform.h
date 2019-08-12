#pragma once

#include <string>

namespace Leviathan
{
	namespace Scene
	{
		class LevRAttrNumericalUniform;
		class LevRAttrTextureUniform;

		enum LevUniformType
		{
			ELUT_NUMERICAL,
			ELUT_TEXTURE,
		};

		class ILevRAttrUniform
		{
		public:
			virtual unsigned GetId() const = 0;
			virtual void SetName(const std::string& name) = 0;
			virtual const std::string& GetName() const = 0;
			virtual LevUniformType GetUniformType() const = 0;
		};
	}
}
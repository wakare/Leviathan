#pragma once

#include "LevSceneAPIDefine.h"
#include "LevTokenDispatch.h"
#include "LPtr.h"
#include "ILevRAttrUniform.h"
#include <string>

namespace Leviathan
{
	namespace Scene
	{
		enum UniformNumericalType
		{
			TYPE_FLOAT_MAT4 = 1,
			TYPE_FLOAT_VEC3 = 2,
			TYPE_BOOLEAN = 3,
			TYPE_INTEGER = 4,
			TYPE_UNSIGNED_INTEGER = 5
		};

		class LEV_SCENE_API LevRAttrNumericalUniform : public ILevRAttrUniform
		{
		public:
			/*
				uniform array must be started with index 1.
			*/
			LevRAttrNumericalUniform(const std::string& name, UniformNumericalType type);

			unsigned GetId() const override;

			void SetName(const std::string& name) override;
			const std::string& GetName() const override;

			void SetData(LPtr<RAIIBufferData> data);
			const RAIIBufferData& GetData() const;

			LevUniformType GetUniformType() const override;
			UniformNumericalType GetNumericalUniformType() const;

		private:
			const unsigned m_uniform_id;
			std::string m_name;
			UniformNumericalType m_uniform_type;
			LPtr<RAIIBufferData> m_data;
		};

		inline LevRAttrNumericalUniform::LevRAttrNumericalUniform(const std::string& name, UniformNumericalType type)
			: m_name(name)
			, m_uniform_type(type)
			, m_uniform_id(LevTokenDispatch<ILevRAttrUniform, unsigned>::GetIncrementToken())
		{
		}

		inline unsigned LevRAttrNumericalUniform::GetId() const
		{
			return m_uniform_id;
		}

		inline void LevRAttrNumericalUniform::SetName(const std::string& name)
		{
			m_name = name;
		}

		inline const std::string & LevRAttrNumericalUniform::GetName() const
		{
			return m_name;
		}

		inline void LevRAttrNumericalUniform::SetData(LPtr<RAIIBufferData> data)
		{
			m_data = data;
		}

		inline const Leviathan::RAIIBufferData& LevRAttrNumericalUniform::GetData() const
		{
			return *m_data;
		}

		inline LevUniformType LevRAttrNumericalUniform::GetUniformType() const
		{
			return ELUT_NUMERICAL;
		}

		inline Leviathan::Scene::UniformNumericalType LevRAttrNumericalUniform::GetNumericalUniformType() const
		{
			return m_uniform_type;
		}

	}
}

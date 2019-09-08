#pragma once

#include "LevSceneAPIDefine.h"
#include "LevTokenDispatch.h"
#include "LSPtr.h"
#include "ILevUniform.h"
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

		class LEV_SCENE_API LevNumericalUniform : public ILevUniform
		{
		public:
			/*
				uniform array must be started with index 1.
			*/
			LevNumericalUniform(const std::string& name, UniformNumericalType type);

			unsigned GetId() const override;

			void SetName(const std::string& name) override;
			const std::string& GetName() const override;

			void SetData(LSPtr<RAIIBufferData> data);
			const RAIIBufferData& GetData() const;

			LevUniformType GetUniformType() const override;
			UniformNumericalType GetNumericalUniformType() const;

		private:
			const unsigned m_uniform_id;
			std::string m_name;
			UniformNumericalType m_uniform_type;
			LSPtr<RAIIBufferData> m_data;
		};

		inline LevNumericalUniform::LevNumericalUniform(const std::string& name, UniformNumericalType type)
			: m_name(name)
			, m_uniform_type(type)
			, m_uniform_id(LevTokenDispatch<ILevUniform, unsigned>::GetIncrementToken())
		{
		}

		inline unsigned LevNumericalUniform::GetId() const
		{
			return m_uniform_id;
		}

		inline void LevNumericalUniform::SetName(const std::string& name)
		{
			m_name = name;
		}

		inline const std::string & LevNumericalUniform::GetName() const
		{
			return m_name;
		}

		inline void LevNumericalUniform::SetData(LSPtr<RAIIBufferData> data)
		{
			m_data = data;
		}

		inline const Leviathan::RAIIBufferData& LevNumericalUniform::GetData() const
		{
			return *m_data;
		}

		inline LevUniformType LevNumericalUniform::GetUniformType() const
		{
			return ELUT_NUMERICAL;
		}

		inline Leviathan::Scene::UniformNumericalType LevNumericalUniform::GetNumericalUniformType() const
		{
			return m_uniform_type;
		}

	}
}

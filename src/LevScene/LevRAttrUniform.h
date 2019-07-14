#pragma once

#include "LevSceneAPIDefine.h"
#include "LevTokenDispatch.h"
#include "LPtr.h"
#include <string>

namespace Leviathan
{
	namespace Scene
	{
		enum UniformType
		{
			TYPE_FLOAT_MAT4 = 1,
			TYPE_FLOAT_VEC3 = 2,
			TYPE_BOOLEAN = 3,
			TYPE_INTEGER = 4,
			TYPE_UNSIGNED_INTEGER = 5
		};

		class LEV_SCENE_API LevRAttrUniform 
		{
		public:
			/*
				uniform array must be started with index 1.
			*/
			LevRAttrUniform(const std::string& name, UniformType type);

			unsigned GetId() const;

			void SetName(std::string name);
			const std::string& GetName() const;

			void SetData(LPtr<RAIIBufferData> data);
			const RAIIBufferData& GetData() const;

			UniformType GetUniformType() const;

		private:
			const unsigned m_uniform_id;
			std::string m_name;
			UniformType m_uniform_type;
			LPtr<RAIIBufferData> m_data;
		};

		inline LevRAttrUniform::LevRAttrUniform(const std::string& name, UniformType type)
			: m_name(name)
			, m_uniform_type(type)
			, m_uniform_id(LevTokenDispatch<LevRAttrUniform, unsigned>::GetToken())
		{
		}

		inline unsigned LevRAttrUniform::GetId() const
		{
			return m_uniform_id;
		}

		inline void LevRAttrUniform::SetName(std::string name)
		{
			m_name = name;
		}

		inline const std::string & LevRAttrUniform::GetName() const
		{
			return m_name;
		}

		inline void LevRAttrUniform::SetData(LPtr<RAIIBufferData> data)
		{
			m_data = data;
		}

		inline const Leviathan::RAIIBufferData& LevRAttrUniform::GetData() const
		{
			return *m_data;
		}

		inline Leviathan::Scene::UniformType LevRAttrUniform::GetUniformType() const
		{
			return m_uniform_type;
		}

	}
}

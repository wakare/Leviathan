#include "LevTextureObject.h"
#include "LevTokenDispatch.h"
#include <utility>

namespace Leviathan
{
	namespace Scene
	{
		Leviathan::Scene::LevTextureObject::LevTextureObject(unsigned width, unsigned height, LPtr<RAIIBufferData> data, const std::string& texture_name)
			: m_id(LevTokenDispatch<LevTextureObject, unsigned>::GetIncrementToken())
			, m_width(width)
			, m_height(height)
			, m_texture_data(std::move(data))
			, m_texture_unifrom_name(texture_name)
		{

		}
		
		unsigned LevTextureObject::GetID() const
		{
			return m_id;
		}

		unsigned LevTextureObject::GetWidth() const
		{
			return m_width;
		}

		unsigned LevTextureObject::GetHeight() const
		{
			return m_height;
		}

		LevTextureObject* LevTextureObject::ToLevTextureObject()
		{
			return this;
		}

		const void* LevTextureObject::GetTextureData() const
		{
			return m_texture_data->GetArrayData();
		}

		const std::string& LevTextureObject::GetTextureUniformName() const
		{
			return m_texture_unifrom_name;
		}
	}
}


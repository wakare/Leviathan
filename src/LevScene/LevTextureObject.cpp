#include "LevTextureObject.h"
#include "LevTokenDispatch.h"
#include <utility>

namespace Leviathan
{
	namespace Scene
	{
		Leviathan::Scene::LevTextureObject::LevTextureObject(LevTextureType texture_type, unsigned width, unsigned height, unsigned depth, LPtr<RAIIBufferData> data, const std::string& texture_uniform_name)
			: m_id(LevTokenDispatch<LevTextureObject, unsigned>::GetIncrementToken())
			, m_texture_type(texture_type)
			, m_width(width)
			, m_height(height)
			, m_depth(depth)
			, m_texture_data(std::move(data))
			, m_texture_uniform_name(texture_uniform_name)
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

		unsigned LevTextureObject::GetDepth() const
		{
			return m_depth;
		}

		LevTextureObject* LevTextureObject::ToLevTextureObject()
		{
			return this;
		}

		LevTextureType LevTextureObject::GetTextureType() const
		{
			return m_texture_type;
		}

		const void* LevTextureObject::GetTextureData() const
		{
			return m_texture_data->GetArrayData();
		}

		const std::string& LevTextureObject::GetTextureUniformName() const
		{
			return m_texture_uniform_name;
		}
	}
}

